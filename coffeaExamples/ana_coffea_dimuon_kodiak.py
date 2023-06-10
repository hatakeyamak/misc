###############################################################################
# Example of Coffea with the Work Queue executor.
#
# To execute, start this application, and then start workers that will connect
# to it and execute tasks.
#
# Note that, as written, this only processes 4 data chunks and should complete
# in a short time.  For a real run, change maxchunks=None in the main program
# below.
#
# For simple testing this script will automatically use one local worker. To
# scale this up, see the wq.Factory configuration below to change to your
# favorite batch system.
###############################################################################

###############################################################################
# Sample processor class given in the Coffea manual.
###############################################################################
#import work_queue as wq 
import ndcctools.work_queue as wq

from coffea.processor import Runner
from coffea.processor import WorkQueueExecutor

###############################################################################
# Collect and display setup info.
###############################################################################

print("------------------------------------------------")
print("Example Coffea Analysis with Work Queue Executor")
print("------------------------------------------------")

import getpass

wq_manager_name = "coffea-wq-{}".format(getpass.getuser())
wq_port = 0

print("Manager Name: -M " + wq_manager_name)
print("------------------------------------------------")


###############################################################################
# Define a custom Coffea processor
###############################################################################

from coffea import processor
from coffea.nanoevents.methods import candidate
from coffea.nanoevents import NanoAODSchema
import hist
from collections import defaultdict
import awkward as ak

# register our candidate behaviors
ak.behavior.update(candidate.behavior)


class MyProcessor(processor.ProcessorABC):
    @property
    def accumulator(self):
        return {
            "sumw": defaultdict(float),
            "sumcut": defaultdict(float),
            "mass": hist.Hist(
                hist.axis.StrCategory([], name="dataset", label="Dataset", growth=True),
                hist.axis.Regular(
                    200, 0.2, 200, name="mass", label=r"$m_{\mu\mu}$ [GeV]"
                )
            ),
        }

    def process(self, events):
        # Note: This is required to ensure that behaviors are registered
        # when running this code in a remote task.
        ak.behavior.update(candidate.behavior)

        output = self.accumulator

        dataset = events.metadata["dataset"]
        muons = events.Muon

        cut = (ak.num(muons) == 2) & (ak.sum(muons.charge, axis=1) == 0)
        # add first and second muon in every event together
        dimuon = muons[cut][:, 0] + muons[cut][:, 1]
        print(dimuon)

        output["sumw"][dataset] += len(events)
        output["sumcut"][dataset] += sum(cut)
        output["mass"].fill(
            dataset=dataset,
            mass=dimuon.mass,
        )

        return output

    def postprocess(self, accumulator):
        return accumulator


###############################################################################
# Sample data sources come from CERN opendata.
###############################################################################

fileset = {
    "DoubleMuon": [
        "root://eospublic.cern.ch//eos/root-eos/cms_opendata_2012_nanoaod/Run2012B_DoubleMuParked.root",
        "root://eospublic.cern.ch//eos/root-eos/cms_opendata_2012_nanoaod/Run2012C_DoubleMuParked.root",
    ],
}


###############################################################################
# Configuration of the Work Queue Executor
###############################################################################

# secret passed between manager and workers for authentication
my_password_file = "password.txt"
with open(my_password_file, "w") as f:
    f.write("this_is_not_a_secure_password")

work_queue_executor_args = {
    # Automatically allocate cores, memory and disk to tasks. Adjusts to
    # maximum values measured. Initially, tasks use whole workers.
    "resources_mode": "auto",
    # Split a processing task in half according to its chunksize when it
    # exhausts the resources allocated to it.
    "split_on_exhaustion": True,
    # Options to control how workers find this manager.
    "manager_name": wq_manager_name,
    # Port for manager to listen on: if zero, will choose automatically.
    "port": wq_port,
    # Secret passed between manager and workers
    "password_file": my_password_file,
    # The named conda environment tarball will be transferred to each worker,
    # and activated. This is useful when coffea is not installed in the remote
    # machines. conda enviroments are created with conda-pack, and should at
    # least include coffea, ndcctools (both from conda-forge channel)
    # and their dependencies.
    "environment_file": "coffea.tar.gz",
    # Debugging: Display notes about each task submitted/complete.
    "verbose": True,
    # Debugging: Display output of task if not empty.
    "print_stdout": False,
    # Debugging: Produce a lot at the manager side of things.
    "debug_log": "coffea-wq.log",
}

executor = WorkQueueExecutor(**work_queue_executor_args)


###############################################################################
# Run the analysis using local Work Queue workers
###############################################################################

import time

tstart = time.time()

workers = wq.Factory(
    # local runs:
    # batch_type="local",
    # manager_host_port="localhost:{}".format(wq_port),
    # with a batch system, e.g., condor.
    # (If coffea not at the installation site, then a conda
    # environment_file should be defined in the work_queue_executor_args.)
    batch_type="pbs", manager_name=wq_manager_name,
)

workers.max_workers = 20
workers.min_workers = 1
workers.cores = 8
workers.memory = 1000  # MB
workers.disk = 2000  # MB
workers.password = my_password_file

# Instead of declaring the python environment per task, you can set it in
# the factory directly. This is useful if you are going to run a workflow
# several times using the same set of workers. It also ensures that the worker
# itself executes in a friendly environment.
workers.python_package = "coffea.tar.gz"
#
# The factory tries to write temporary files to $TMPDIR (usually /tmp). When
# this is not available, or causes errors, this scracth directory can be
# manually set.
workers.scratch_dir = "./my-scratch-dir"

with workers:
    # define the Runner instance
    run_fn = Runner(
        executor=executor,
        schema=NanoAODSchema,
        chunksize=100000,
        maxchunks=4,  # change this to None for a large run
        #maxchunks=None,  # change this to None for a large run
    )
    # execute the analysis on the given dataset
    hists = run_fn(fileset, "Events", MyProcessor())

elapsed = time.time() - tstart


print(hists)
print(hists["mass"])

# (assert only valid when using maxchunks=4)
assert hists["sumw"]["DoubleMuon"] == 400224

###### Now actually display the histogram we created

import matplotlib.pyplot as plt

fig, ax = plt.subplots()
h = hists["mass"]
h.plot1d(ax=ax)
plt.legend()
plt.xscale('log')
plt.yscale('log')
plt.savefig('mass.png')
