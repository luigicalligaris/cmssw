import FWCore.ParameterSet.Config as cms


process = cms.Process("DTCBandwidthStatisticsAnalyzerDEMO")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')


# Load CondDB service
process.load("CondCore.CondDB.CondDB_cfi")
# input database (in this case the local sqlite file)
process.CondDB.connect = 'sqlite_file:OuterTrackerDTCCablingMap.db'

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    process.CondDB,
    #DumpStat=cms.untracked.bool(True),
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('OuterTrackerDTCCablingMapRcd'),
        tag = cms.string("DTCCablingTest")
    )),
)

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
		#'file:output_0.root',
		#'root://cmsxrootd.fnal.gov/',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/003EF948-9F7E-E711-8EC9-24BE05C6E571.root',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/00C9BA0B-9F7E-E711-9269-5065F3815221.root',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/02C15900-A37E-E711-AEEC-5065F3815241.root',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/049FB523-9E7E-E711-9D5F-5065F381F2D2.root',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/06423504-A37E-E711-8D7D-E0071B7A18F0.root',
		'/store/relval/CMSSW_9_3_0_pre3/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_92X_upgrade2023_realistic_v2_D17PU200-v2/00000/08BA86FA-9F7E-E711-886C-24BE05CECDD1.root'
		)
	)

process.TFileService = cms.Service("TFileService", 
		fileName = cms.string("histo.root"),
		closeFileFast = cms.untracked.bool(False)
)

process.dtcbandwidthstatisticsanalyzer = cms.EDAnalyzer("DTCBandwidthStatisticsAnalyzer",
	#PrintLevel = cms.uint32(2), # Debug printout level
	#NumEvents = cms.uint32(NEVENTS), # Number of events used for study.
	#ClustersInputTag = cms.InputTag("TTStubsFromPhase2TrackerDigis","ClusterAccepted","HLT"),
	HitsInputTag = cms.InputTag("mix"                               ,"Tracker"           ,"HLT"),
	ClusInputTag = cms.InputTag("TTClustersFromPhase2TrackerDigis"  ,"ClusterInclusive"  ,"HLT"),
	StubInputTag = cms.InputTag("TTStubsFromPhase2TrackerDigis"     ,"StubAccepted"      ,"HLT"),
	)

process.path = cms.Path(process.dtcbandwidthstatisticsanalyzer)
