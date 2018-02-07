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
#include <mutex>

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
#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"

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
		
// 		using DetSetVec  = edmNew::DetSetVector< Phase2TrackerCluster1D >;
// 		using DetSet     = edmNew::DetSet< Phase2TrackerCluster1D >      ;
// 		using ClusterRef = edm::Ref< DetSetVec, Phase2TrackerCluster1D > ;
		
		using TTCl          = TTCluster<edm::Ref<edm::DetSetVector<Phase2TrackerDigi>, Phase2TrackerDigi, edm::refhelper::FindForDetSetVector<Phase2TrackerDigi> > >;
		using TTSt          = TTStub   <edm::Ref<edm::DetSetVector<Phase2TrackerDigi>, Phase2TrackerDigi, edm::refhelper::FindForDetSetVector<Phase2TrackerDigi> > >;
		
		using TTClDetSet              = edmNew::DetSet< TTCl >;
		using TTStDetSet              = edmNew::DetSet< TTSt >;
		using Phase2TrackerDigiDetSet = edm::DetSet<Phase2TrackerDigi>;
		
		using TTClDetSetVec              = edmNew::DetSetVector< TTCl >;
		using TTStDetSetVec              = edmNew::DetSetVector< TTSt >;
		using Phase2TrackerDigiDetSetVec = edm::DetSetVector<Phase2TrackerDigi>;
		
		using TTClusterRef  = edm::Ref< TTClDetSetVec, TTCl >;
		using TTStubRef     = edm::Ref< TTStDetSetVec, TTSt >;
		
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
		
// 		TrackerGeometry           const* trackerGeom_;
// 		TrackerTopology           const* trackerTopo_;
// 		OuterTrackerDTCCablingMap const* dtcCablingMap_;
		
		TFileDirectory tfs_dir_hardware_;
		TFileDirectory tfs_dir_datarates_;
		
		TH1F*     h1_nmodules_per_dtc_      ;
		TProfile* hprof1_nclusters_per_dtc_ ;
		TProfile* hprof1_nhits_per_dtc_     ;
		TProfile* hprof1_nstubs_per_dtc_    ;
		
		edm::ESHandle<OuterTrackerDTCCablingMap> outerTrackerDTCCablingMapHandle_;
		
		edm::Service<TFileService> fs_;
		std::unordered_set<DTCId> allDTCsInCablingMap_;
		
		edm::EDGetTokenT<Phase2TrackerDigiDetSetVec> const hitsInputTag_;
		edm::EDGetTokenT<TTClDetSetVec>              const clusInputTag_;
		edm::EDGetTokenT<TTStDetSetVec>              const stubInputTag_;
		
};


void DTCBandwidthStatisticsAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DTCBandwidthStatisticsAnalyzer::DTCBandwidthStatisticsAnalyzer(edm::ParameterSet const& iConfig):
// 	clusInputTag_( consumes<DetSetVec>( iConfig.getParameter<edm::InputTag>("ClusInputTag") ) )
	hitsInputTag_( consumes<Phase2TrackerDigiDetSetVec>( iConfig.getParameter<edm::InputTag>("HitsInputTag") ) ),
	clusInputTag_( consumes<TTClDetSetVec>             ( iConfig.getParameter<edm::InputTag>("ClusInputTag") ) ),
	stubInputTag_( consumes<TTStDetSetVec>             ( iConfig.getParameter<edm::InputTag>("StubInputTag") ) )
{
	usesResource("TFileService");
	
}

void DTCBandwidthStatisticsAnalyzer::beginJob()
{
	
}

void DTCBandwidthStatisticsAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	using namespace std;
	
}

void DTCBandwidthStatisticsAnalyzer::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
	using namespace std;
	
	edm::Handle<Phase2TrackerDigiDetSetVec> hitsHandle;
	edm::Handle<TTClDetSetVec>              clusHandle;
	edm::Handle<TTStDetSetVec>              stubHandle;
	
	iSetup.get<OuterTrackerDTCCablingMapRcd>().get(outerTrackerDTCCablingMapHandle_);
	
	iEvent.getByToken(hitsInputTag_, hitsHandle);
	iEvent.getByToken(clusInputTag_, clusHandle);
	iEvent.getByToken(stubInputTag_, stubHandle);
	
// 	cout << "clusHandle->size() = " << clusHandle->size() << endl;
// 	cout << "stubHandle->size() = " << stubHandle->size() << endl;  
	
	
	// Book histograms here, rather than in constructor, so we know how many DTCs there are.
	static bool firstEvent = true;
	
	if (firstEvent)
	{
		firstEvent = false;
		
		size_t const numDTCs = outerTrackerDTCCablingMapHandle_->knownDTCIds_.size();
		
		// Instantiate the histograms
		tfs_dir_hardware_ = fs_->mkdir("Hardware");
		h1_nmodules_per_dtc_ = tfs_dir_hardware_.make<TH1F>    ("h1_nmodules_per_dtc"      ,"Number Of Modules per DTC;DTC identifier;N_{modules}"         , numDTCs, -0.5, -0.5+numDTCs);
		
		tfs_dir_datarates_ = fs_->mkdir("DataRates");
		hprof1_nclusters_per_dtc_  = tfs_dir_datarates_.make<TProfile>("hprof1_nclusters_per_dtc" ,"Number Of Average Clusters per DTC;DTC identifier;N_{clusters}", numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nhits_per_dtc_      = tfs_dir_datarates_.make<TProfile>("hprof1_nhits_per_dtc"     ,"Number Of Average Hits per DTC;DTC identifier;N_{hits}"    , numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nstubs_per_dtc_     = tfs_dir_datarates_.make<TProfile>("hprof1_nstubs_per_dtc"    ,"Number Of Average Stubs per DTC;DTC identifier;N_{stubs}"   , numDTCs, -0.5, -0.5+numDTCs);
		
		
		hprof1_nclusters_per_dtc_->GetXaxis()->SetLabelSize(0.005);
		hprof1_nhits_per_dtc_    ->GetXaxis()->SetLabelSize(0.005);
		hprof1_nstubs_per_dtc_   ->GetXaxis()->SetLabelSize(0.005);
		h1_nmodules_per_dtc_     ->GetXaxis()->SetLabelSize(0.005);
		
		
		// Fill Hardware histograms
		for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
		{
			size_t const nModules = outerTrackerDTCCablingMapHandle_->cablingMapDTCIdToDetId_.count(dtc_ref);
			
			h1_nmodules_per_dtc_     ->Fill(dtc_ref.name(), nModules);
		}
		
		
		// Prepare bins in rate histograms
		for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
		{
			hprof1_nclusters_per_dtc_->Fill(dtc_ref.name(), 0.0);
			hprof1_nhits_per_dtc_    ->Fill(dtc_ref.name(), 0.0);
			hprof1_nstubs_per_dtc_   ->Fill(dtc_ref.name(), 0.0);
		}
	}
	
	std::unordered_map<DTCId, unsigned int> hitCounts;
	std::unordered_map<DTCId, unsigned int> cluCounts;
	std::unordered_map<DTCId, unsigned int> stuCounts;
	
	for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
	{
		hitCounts[dtc_ref] = 0;
		cluCounts[dtc_ref] = 0;
		stuCounts[dtc_ref] = 0;
	}
	
	
	for (auto const& hit: *hitsHandle)
	{
		uint32_t const detId = hit.detId();
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& hitDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
// 			string const hitDTCName = hitDTC.name();
			
			++hitCounts[hitDTC];
		}
		else
		{
			cout << "hit DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	for (auto const& clu: *clusHandle)
	{
		uint32_t const detId = clu.detId();
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& cluDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
// 			string const cluDTCName = cluDTC.name();
			
			++cluCounts[cluDTC];
		}
		else
		{
			cout << "cluster DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	for (auto const& stu: *stubHandle)
	{
		uint32_t const detId = stu.detId();
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& cluDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
			string const cluDTCName = cluDTC.name();
			
			++stuCounts[cluDTC];
		}
		else
		{
			cout << "stub DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
	{
		hprof1_nhits_per_dtc_    ->Fill(dtc_ref.name(), double(hitCounts[dtc_ref]));
		hprof1_nclusters_per_dtc_->Fill(dtc_ref.name(), double(cluCounts[dtc_ref]) );
		hprof1_nstubs_per_dtc_   ->Fill(dtc_ref.name(), double(stuCounts[dtc_ref]) );
	}
}

void DTCBandwidthStatisticsAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	
}

void DTCBandwidthStatisticsAnalyzer::endJob() 
{
	
}

DTCBandwidthStatisticsAnalyzer::~DTCBandwidthStatisticsAnalyzer()
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCBandwidthStatisticsAnalyzer);
