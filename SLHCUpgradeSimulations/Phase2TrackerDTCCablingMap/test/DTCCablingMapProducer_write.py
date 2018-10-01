import FWCore.ParameterSet.Config as cms

process = cms.Process("DTCCablingMapTestProducerWriteDEMO")

process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')

# Load CondDB service
process.load("CondCore.CondDB.CondDB_cfi")

# output database (in this case local sqlite file)
process.CondDB.connect = 'sqlite_file:OuterTrackerDTCCablingMap.db'

# A data source must always be defined. We don't need it, so here's a dummy one.
process.source = cms.Source("EmptyIOVSource",
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue = cms.uint64(1),
    interval = cms.uint64(1)
)

# We define the output service.
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDB,
    timetype = cms.untracked.string('runnumber'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('OuterTrackerDTCCablingMapRcd'),
        tag = cms.string('DTCCablingTest')
    ))
)

process.otdtccablingmap_producer = cms.EDAnalyzer("DTCCablingMapProducer",
    record = cms.string('OuterTrackerDTCCablingMapRcd'),
    inputCablingFileName = cms.FileInPath("SLHCUpgradeSimulations/Phase2TrackerDTCCablingMap/data/ModulesToDTCsT5_v4.csv"),
    verbosity = cms.int32(0),
    #loggingOn= cms.untracked.bool(True),
    #SinceAppendMode=cms.bool(True),
    #Source=cms.PSet(
        #IOVRun=cms.untracked.uint32(1)
    #)
)

process.path = cms.Path(process.otdtccablingmap_producer)

