import FWCore.ParameterSet.Config as cms

process = cms.Process("DTCBandwidthStatisticsAnalyzerDEMO")

# Load CondDB service
process.load("CondCore.CondDB.CondDB_cfi")

# input database (in this case the local sqlite file)
process.CondDB.connect = 'sqlite_file:OuterTrackerDTCCablingMap.db'

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    process.CondDB,
    #DumpStat=cms.untracked.bool(True),
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('OuterTrackerDTCCablingMapRcd'),
        tag = cms.string("DTCCablingMapProducer_test")
    )),
)

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
		'file:output_0.root'
		)
	)

process.TFileService = cms.Service("TFileService", 
		fileName = cms.string("histo.root"),
		closeFileFast = cms.untracked.bool(False)
)

process.otdtccablingmap_producer = cms.EDAnalyzer("DTCBandwidthStatisticsAnalyzer",
	#PrintLevel = cms.uint32(2), # Debug printout level
	#NumEvents = cms.uint32(NEVENTS), # Number of events used for study.
	ClusInputTag = cms.InputTag("siPhase2Clusters"), 
	)

process.path = cms.Path(process.otdtccablingmap_producer)
