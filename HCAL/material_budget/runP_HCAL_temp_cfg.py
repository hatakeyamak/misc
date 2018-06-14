import FWCore.ParameterSet.Config as cms
import math

process = cms.Process("PROD")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

#Geometry
#
process.load('Configuration.Geometry.GeometryECALHCAL_cff')
#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
#process.load("Geometry.TrackerNumberingBuilder.trackerNumberingGeometry_cfi")

#Magnetic Field
#
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("Configuration.EventContent.EventContent_cff")

# Detector simulation (Geant4-based)
#
process.load("SimG4Core.Application.g4SimHits_cfi")

process.load('Configuration.StandardSequences.Services_cff')

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

process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring('detailedInfo_towerTOWERNAMETBORNAME_phiPHISTEP_PHINUM'),
    categories = cms.untracked.vstring('MaterialBudget'),
    debugModules = cms.untracked.vstring('*'),
    detailedInfo_towerTOWERNAMETBORNAME_phiPHISTEP_PHINUM = cms.untracked.PSet(
        threshold = cms.untracked.string('DEBUG'),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        MaterialBudget = cms.untracked.PSet(
            limit = cms.untracked.int32(-1)
        )
    )
)

process.source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring('file:single_neutrino_towerTOWERNAMETBORNAME_phiPHISTEP_PHINUM.root')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('matbdg_HCAL_towerTOWERNAMETBORNAME_phiPHISTEP_PHINUM.root')
)

process.p1 = cms.Path(process.g4SimHits)
process.g4SimHits.UseMagneticField = False
process.g4SimHits.Physics.type = 'SimG4Core/Physics/DummyPhysics'
process.g4SimHits.Physics.DummyEMPhysics = True
process.g4SimHits.Physics.CutsPerRegion = False
process.g4SimHits.Watchers = cms.VPSet(cms.PSet(
    MaterialBudgetHcal = cms.PSet(
        FillHisto    = cms.untracked.bool(True),
        PrintSummary = cms.untracked.bool(True),
        DoHCAL       = cms.untracked.bool(True),
        NBinPhi      = cms.untracked.int32(360),
        NBinEta      = cms.untracked.int32(1),
        MaxEta       = cms.untracked.double(5.2),
        EtaLow       = cms.untracked.double(etaval),
        EtaHigh      = cms.untracked.double(etaval),
        RMax         = cms.untracked.double(5.0),
        ZMax         = cms.untracked.double(14.0)
    ),
    type = cms.string('MaterialBudgetHcal')
))


