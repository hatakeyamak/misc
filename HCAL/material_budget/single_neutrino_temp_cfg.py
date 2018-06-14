import FWCore.ParameterSet.Config as cms
import math

process = cms.Process("TestProcess")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource",
    firstRun        = cms.untracked.uint32(1),
    firstEvent      = cms.untracked.uint32(1)
)

#select center eta or borders (+/-1)
tower_num = TOWERNUM
tower_numa = abs(tower_num)
tower_etas = [1.305,1.392,1.479,1.566,1.653,1.740,1.830,1.930,2.043,2.172,2.322,2.500,2.650,2.868,3.000]
if TOWERPOS==0:
    etaval = (tower_etas[tower_numa-16]+tower_etas[tower_numa-16+1])/2
elif TOWERPOS==-1:
    etaval = tower_etas[tower_numa-16]
elif TOWERPOS==1:
    etaval = tower_etas[tower_numa-16+1]

if tower_num < 0:
    etaval = -etaval
    
print "Eta value: "+str(etaval)+" (Tower "+str(tower_num)+")"

#phi spans 0 to 2*pi
phival = (PHISTEP*PHINUM)*math.pi/180
print "Phi value: "+str(phival)

process.generator = cms.EDFilter("Pythia8EGun",
    PGunParameters = cms.PSet(
        AddAntiParticle = cms.bool(False),
        ParticleID = cms.vint32(14),
        MinEta = cms.double(etaval),
        MaxEta = cms.double(etaval),
        MinPhi = cms.double(phival),
        MaxPhi = cms.double(phival),
        MinE   = cms.double(10.0),
        MaxE   = cms.double(10.0)
    ),
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring()
    ),
    Verbosity = cms.untracked.int32(0),
    firstRun = cms.untracked.uint32(1),
    psethack = cms.string('single mu pt 10')
)

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('file:single_neutrino_towerTOWERNAMETBORNAME_phiPHISTEP_PHINUM.root'),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.generation_step = cms.Path(process.pgen)
process.outpath = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.outpath)

# filter all path with the production filter sequence
for path in process.paths:
        getattr(process,path)._seq = process.generator * getattr(process,path)._seq 
