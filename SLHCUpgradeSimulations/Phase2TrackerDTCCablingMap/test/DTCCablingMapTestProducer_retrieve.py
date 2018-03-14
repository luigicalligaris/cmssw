import FWCore.ParameterSet.Config as cms

process = cms.Process("DTCCablingMapProducerRetrieveDEMO")

process.load("CondCore.CondDB.CondDB_cfi")
# input database (in this case the local sqlite file)
process.CondDB.connect = 'sqlite_file:OuterTrackerDTCCablingMap.db'

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    process.CondDB,
    DumpStat=cms.untracked.bool(True),
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('OuterTrackerDTCCablingMapRcd'),
        tag = cms.string("DTCCablingTest")
    )),
)

process.get = cms.EDAnalyzer("EventSetupRecordDataGetter",
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('OuterTrackerDTCCablingMapRcd'),
        data = cms.vstring('OuterTrackerDTCCablingMap')
    )),
    verbose = cms.untracked.bool(True)
)

# A data source must always be defined. We don't need it, so here's a dummy one.
process.source = cms.Source("EmptyIOVSource",
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue = cms.uint64(1),
    interval = cms.uint64(1)
)

process.path = cms.Path(process.get)
