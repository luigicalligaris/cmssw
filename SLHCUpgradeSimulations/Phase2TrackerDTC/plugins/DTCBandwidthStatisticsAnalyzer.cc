// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/Phase2TrackerDTC
// Class:      DTCBandwidthStatisticsAnalyzer
// 
/**\class DTCBandwidthStatisticsAnalyzer DTCBandwidthStatisticsAnalyzer.cc SLHCUpgradeSimulations/Phase2TrackerDTC/plugins/DTCBandwidthStatisticsAnalyzer.cc

Description: [one line class summary]

Implementation:
		[Notes on implementation]
*/
//
// Original Author:  Luigi Calligaris, SPRACE, São Paulo, BR
//         Created:  Tue, 30 Jan 2018 13:28:49 GMT
//
//

#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>

#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Phase2TrackerCluster/interface/Phase2TrackerCluster1D.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
// #include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
// #include "Geometry/CommonTopologies/interface/PixelTopology.h"

#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondFormats/Phase2TrackerObjects/interface/OuterTrackerDTCCablingMap.h"
#include "CondFormats/DataRecord/interface/OuterTrackerDTCCablingMapRcd.h"

#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"

#include "TH1.h"
#include "TProfile.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TFile.h"


class DTCBandwidthStatisticsAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
	public:
		
		using DetSetVec  = edmNew::DetSetVector< Phase2TrackerCluster1D >;
		using DetSet     = edmNew::DetSet< Phase2TrackerCluster1D >      ;
		using ClusterRef = edm::Ref< DetSetVec, Phase2TrackerCluster1D > ;
		
		explicit DTCBandwidthStatisticsAnalyzer(const edm::ParameterSet&);
		~DTCBandwidthStatisticsAnalyzer();
		
		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
		
	private:
		virtual void beginJob() override;
		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
// 		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&) override;
		
		virtual void analyze(edm::Event const&, const edm::EventSetup&) override;
		
// 		virtual void endLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&) override;
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void endJob() override;
	private:
		// Remember that for space efficiency you should order data members by size, due to alignment requirements of the C++ standard
		
		TrackerGeometry           const* trackerGeom_;
		TrackerTopology           const* trackerTopo_;
		OuterTrackerDTCCablingMap const* dtcCablingMap_;
		
		TFileDirectory tfs_dir_hardware_;
		TFileDirectory tfs_dir_datarates_;
		
		TH1F*     h1_nmodules_per_dtc_      ;
		TProfile* hprof1_nclusters_per_dtc_ ;
		TProfile* hprof1_nhits_per_dtc_     ;
		TProfile* hprof1_nstubs_per_dtc_    ;
		
		edm::Service<TFileService> fs_;
		std::unordered_set<DTCId> allDTCsInCablingMap_;
		
		edm::EDGetTokenT<DetSetVec> const clusInputTag_;
		
};


void DTCBandwidthStatisticsAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DTCBandwidthStatisticsAnalyzer::DTCBandwidthStatisticsAnalyzer(const edm::ParameterSet& iConfig):
	clusInputTag_( consumes<DetSetVec>( iConfig.getParameter<edm::InputTag>("ClusInputTag") ) )
{
	usesResource("TFileService");
	
}

void DTCBandwidthStatisticsAnalyzer::beginJob()
{
	
}

void DTCBandwidthStatisticsAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	using namespace std;
	
	// Book histograms here, rather than in constructor, so we know how many DTCs there are.
	static bool first = true;
	
	if (first)
	{
		first = false;
		
		edm::ESHandle<TrackerGeometry> trackerGeometryHandle;
		iSetup.get<TrackerDigiGeometryRecord>().get(trackerGeometryHandle);
		trackerGeom_ = trackerGeometryHandle.product();
		
		edm::ESHandle<TrackerTopology> trackerTopologyHandle;
		iSetup.get<TrackerTopologyRcd>().get(trackerTopologyHandle);
		trackerTopo_ = trackerTopologyHandle.product();
		
		edm::ESHandle<OuterTrackerDTCCablingMap> outerTrackerDTCCablingMapHandle;
		iSetup.get<OuterTrackerDTCCablingMapRcd>().get(outerTrackerDTCCablingMapHandle);
		dtcCablingMap_ = outerTrackerDTCCablingMapHandle.product();
		
		for (auto const& pair_ref : dtcCablingMap_->cablingMapDTCToDet_)
		{
			allDTCsInCablingMap_.insert(DTCId(pair_ref.first));
		}
		
		size_t const numDTCs = allDTCsInCablingMap_.size();
		
		
		// Instantiate the histograms
		
		tfs_dir_hardware_ = fs_->mkdir("Hardware");
		h1_nmodules_per_dtc_ = tfs_dir_hardware_.make<TH1F>    ("h1_nmodules_per_dtc"      ,"Number Of Modules per DTC;DTC identifier;N_{modules}"         , numDTCs, -0.5, -0.5+numDTCs);
		
		tfs_dir_datarates_ = fs_->mkdir("DataRates");
		hprof1_nclusters_per_dtc_  = tfs_dir_datarates_.make<TProfile>("hprof1_nclusters_per_dtc" ,"Number Of Average Clusters per DTC;DTC identifier;N_{modules}", numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nhits_per_dtc_      = tfs_dir_datarates_.make<TProfile>("hprof1_nhits_per_dtc"     ,"Number Of Average Hits per DTC;DTC identifier;N_{modules}"    , numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nstubs_per_dtc_     = tfs_dir_datarates_.make<TProfile>("hprof1_nstubs_per_dtc"    ,"Number Of Average Stubs per DTC;DTC identifier;N_{modules}"   , numDTCs, -0.5, -0.5+numDTCs);
		
	}
}

void DTCBandwidthStatisticsAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	
	using namespace std;
	
	static bool first = true;
	
	if (first)
	{
		first = false;
		
		// Fill Hardware histograms
		
		for (auto const& dtc_ref : allDTCsInCablingMap_)
		{
			size_t const nModules = dtcCablingMap_->cablingMapDTCToDet_.count(dtc_ref);
			
			h1_nmodules_per_dtc_->Fill(dtc_ref.name(),nModules);
		}
	}
}

void DTCBandwidthStatisticsAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	
}

void DTCBandwidthStatisticsAnalyzer::endJob() 
{
// 	h1_nmodules_per_dtc_       ->Write();
// 	hprof1_nclusters_per_dtc_  ->Write();
// 	hprof1_nhits_per_dtc_      ->Write();
// 	hprof1_nstubs_per_dtc_     ->Write();
}

DTCBandwidthStatisticsAnalyzer::~DTCBandwidthStatisticsAnalyzer()
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCBandwidthStatisticsAnalyzer);
