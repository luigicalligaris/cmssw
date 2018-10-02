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
        tag = cms.string('DTCCablingMapProducerUserRun')
    ))
)

process.otdtccablingmap_producer = cms.EDAnalyzer("DTCCablingMapProducer",
    record = cms.string('OuterTrackerDTCCablingMapRcd'),
    modulesToDTCCablingCSVFileNames = cms.vstring("SLHCUpgradeSimulations/Phase2TrackerDTCCablingMap/data/OT613_200_IT4025__ModulesToDTCsAllOuter.csv"),
    #csvFormat_ncolumns = cms.int32(15),
    #csvFormat_idetid   = cms.int32( 0),
    #csvFormat_idtcid   = cms.int32(10),
    #verbosity = cms.int32(3),
    #loggingOn= cms.untracked.bool(True),
    #SinceAppendMode=cms.bool(True),
    #Source=cms.PSet(
        #IOVRun=cms.untracked.uint32(1)
    #)
)

process.path = cms.Path(process.otdtccablingmap_producer)

