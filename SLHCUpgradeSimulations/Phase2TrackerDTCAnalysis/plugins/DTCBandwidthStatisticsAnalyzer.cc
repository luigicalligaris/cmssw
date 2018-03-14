// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/Phase2TrackerDTCAnalysis
// Class:      DTCBandwidthStatisticsAnalyzer
// 
/**\class DTCBandwidthStatisticsAnalyzer DTCBandwidthStatisticsAnalyzer.cc SLHCUpgradeSimulations/Phase2TrackerDTCAnalysis/plugins/DTCBandwidthStatisticsAnalyzer.cc

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
#include <algorithm>
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
// #include "DataFormats/SiStripDetId/interface/TIDDetId.h"
// #include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"

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
#include "TH2.h"
#include "TProfile.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TFile.h"


class DTCBandwidthStatisticsAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
	public:
		
		using P2Di = Phase2TrackerDigi;
// 		using TTCl = TTCluster<edm::Ref<edm::DetSetVector<P2Di>, P2Di, edm::refhelper::FindForDetSetVector<P2Di> > >;
		using P2Cl = Phase2TrackerCluster1D;
		using TTSt = TTStub   <edm::Ref<edm::DetSetVector<P2Di>, P2Di, edm::refhelper::FindForDetSetVector<P2Di> > >;
		
		using P2DiDetSet = edm::DetSet< P2Di >;
// 		using TTClDetSet = edmNew::DetSet< TTCl >;
		using P2ClDetSet = edmNew::DetSet< P2Cl >;
		using TTStDetSet = edmNew::DetSet< TTSt >;
		
		using P2DiDetSetVec = edm::DetSetVector< P2Di >;
// 		using TTClDetSetVec = edmNew::DetSetVector< TTCl >;
		using P2ClDetSetVec = edmNew::DetSetVector< P2Cl >;
		using TTStDetSetVec = edmNew::DetSetVector< TTSt >;
		
		using P2DiRef = edm::Ref< P2DiDetSetVec, P2Di >;
// 		using TTClRef = edm::Ref< TTClDetSetVec, TTCl >;
		using P2ClRef = edm::Ref< P2ClDetSetVec, P2Cl > ;
		using TTStRef = edm::Ref< TTStDetSetVec, TTSt >;
		
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
		
		std::unordered_map<DTCId, unsigned int>  max_nclusters_per_dtc_ ;
		std::unordered_map<DTCId, unsigned int>  max_nhits_per_dtc_     ;
		std::unordered_map<DTCId, unsigned int>  max_nstubs_per_dtc_    ;
		
		TH1F*     h1_nmodules_per_dtc_      ;
		
		TH1F*     hmax1_nhits_per_dtc_      ;
		TH1F*     hmax1_nclusters_per_dtc_  ;
		TH1F*     hmax1_nstubs_per_dtc_     ;
		TH1F*     h1_nstubs_in_ps10g_1_     ;
		TH1F*     h1_nstubs_in_ps10g_2_     ;
		TH2F*     h2_daqrate_per_dtc_       ;
		TH2F*     h2_daqrate_per_dth_       ;
		TH2F*     h2_nhits_per_dtc_         ;
		TH2F*     h2_nclusters_per_dtc_     ;
		TH2F*     h2_nstubs_per_dtc_        ;
		TProfile* hprof1_nhits_per_dtc_     ;
		TProfile* hprof1_nclusters_per_dtc_ ;
		TProfile* hprof1_nstubs_per_dtc_    ;
		
		std::unordered_map<DTCId, unsigned int> dtcBinningMap_;
		
		edm::ESHandle<OuterTrackerDTCCablingMap> outerTrackerDTCCablingMapHandle_;
		
		edm::Service<TFileService> fs_;
		std::unordered_set<DTCId> allDTCsInCablingMap_;
		
		edm::EDGetTokenT<P2DiDetSetVec> const hitsInputTag_;
// 		edm::EDGetTokenT<TTClDetSetVec> const clusInputTag_;
		edm::EDGetTokenT<P2ClDetSetVec> const clusInputTag_;
		edm::EDGetTokenT<TTStDetSetVec> const stubInputTag_;
		
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
	hitsInputTag_( consumes<P2DiDetSetVec>( iConfig.getParameter<edm::InputTag>("HitsInputTag") ) ),
// 	clusInputTag_( consumes<TTClDetSetVec>( iConfig.getParameter<edm::InputTag>("ClusInputTag") ) ),
	clusInputTag_( consumes<P2ClDetSetVec>( iConfig.getParameter<edm::InputTag>("ClusInputTag") ) ),
	stubInputTag_( consumes<TTStDetSetVec>( iConfig.getParameter<edm::InputTag>("StubInputTag") ) )
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
	
	edm::ESHandle<TrackerTopology> trackerTopoHandle;
	iSetup.get<TrackerTopologyRcd>().get( trackerTopoHandle );
	
	edm::ESHandle< TrackerGeometry > trackerGeomHandle;
	iSetup.get< TrackerDigiGeometryRecord >().get( trackerGeomHandle );
	
	
	edm::Handle<P2DiDetSetVec> hitsHandle;
// 	edm::Handle<TTClDetSetVec> clusHandle;
	edm::Handle<P2ClDetSetVec> clusHandle;
	edm::Handle<TTStDetSetVec> stubHandle;
	
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
		hmax1_nhits_per_dtc_       = tfs_dir_datarates_.make<TH1F>("hmax1_nhits_per_dtc"          ,"Max number of hits per DTC;DTC identifier;N_{hits}"                       , numDTCs, -0.5, -0.5+numDTCs);
		hmax1_nclusters_per_dtc_   = tfs_dir_datarates_.make<TH1F>("hmax1_nclusters_per_dtc"      ,"Max number of clusters per DTC;DTC identifier;N_{clusters}"               , numDTCs, -0.5, -0.5+numDTCs);
		hmax1_nstubs_per_dtc_      = tfs_dir_datarates_.make<TH1F>("hmax1_nstubs_per_dtc"         ,"Max number of stubs per DTC;DTC identifier;N_{stubs}"                     , numDTCs, -0.5, -0.5+numDTCs);
		h1_nstubs_in_ps10g_1_      = tfs_dir_datarates_.make<TH1F>("h1_nstubs_in_ps10g_1"         ,"Distribution of number of stubs for PS10G_1 DTC;DTC identifier;N_{hits}"  , 200, 0.0, 400.0);
		h1_nstubs_in_ps10g_2_      = tfs_dir_datarates_.make<TH1F>("h1_nstubs_in_ps10g_2"         ,"Distribution of number of stubs for PS10G_2 DTC;DTC identifier;N_{stubs}" , 200, 0.0, 400.0);
		h2_daqrate_per_dtc_        = tfs_dir_datarates_.make<TH2F>("h2_daqrate_per_dtc"           ,"Data rate per DTC;DTC identifier;Rate [Gbps]"                             , numDTCs, -0.5, -0.5+numDTCs,  100,0,  100.);
		h2_daqrate_per_dth_        = tfs_dir_datarates_.make<TH2F>("h2_daqrate_per_dth"           ,"Data rate per DTH;DTH number;Rate [Gbps]"                                 ,      18, -0.5,      -0.5+18,  200,0, 1000.);
		h2_nhits_per_dtc_          = tfs_dir_datarates_.make<TH2F>("h2_nhits_per_dtc"             ,"Number of hits per DTC;DTC identifier;N_{hits}"                           , numDTCs, -0.5, -0.5+numDTCs,  200,0,10000.);
		h2_nclusters_per_dtc_      = tfs_dir_datarates_.make<TH2F>("h2_nclusters_per_dtc"         ,"Number of clusters per DTC;DTC identifier;N_{clusters}"                   , numDTCs, -0.5, -0.5+numDTCs,  200,0, 5000.);
		h2_nstubs_per_dtc_         = tfs_dir_datarates_.make<TH2F>("h2_nstubs_per_dtc"            ,"Number of stubs per DTC;DTC identifier;N_{stubs}"                         , numDTCs, -0.5, -0.5+numDTCs,  200,0,  400.);
		hprof1_nhits_per_dtc_      = tfs_dir_datarates_.make<TProfile>("hprof1_nhits_per_dtc"     ,"Number of average hits per DTC;DTC identifier;N_{hits}"                   , numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nclusters_per_dtc_  = tfs_dir_datarates_.make<TProfile>("hprof1_nclusters_per_dtc" ,"Number of average clusters per DTC;DTC identifier;N_{clusters}"           , numDTCs, -0.5, -0.5+numDTCs);
		hprof1_nstubs_per_dtc_     = tfs_dir_datarates_.make<TProfile>("hprof1_nstubs_per_dtc"    ,"Number of average stubs per DTC;DTC identifier;N_{stubs}"                 , numDTCs, -0.5, -0.5+numDTCs);
		
		h1_nmodules_per_dtc_      ->GetXaxis()->SetLabelSize(0.005);
		hmax1_nclusters_per_dtc_  ->GetXaxis()->SetLabelSize(0.005);
		hmax1_nhits_per_dtc_      ->GetXaxis()->SetLabelSize(0.005);
		hmax1_nstubs_per_dtc_     ->GetXaxis()->SetLabelSize(0.005);
		h1_nstubs_in_ps10g_1_     ->GetXaxis()->SetLabelSize(0.05);
		h1_nstubs_in_ps10g_2_     ->GetXaxis()->SetLabelSize(0.05);
		h2_daqrate_per_dtc_       ->GetXaxis()->SetLabelSize(0.005);
		h2_daqrate_per_dth_       ->GetXaxis()->SetLabelSize(0.05);
		h2_nhits_per_dtc_         ->GetXaxis()->SetLabelSize(0.005);
		h2_nclusters_per_dtc_     ->GetXaxis()->SetLabelSize(0.005);
		h2_nstubs_per_dtc_        ->GetXaxis()->SetLabelSize(0.005);
		hprof1_nclusters_per_dtc_ ->GetXaxis()->SetLabelSize(0.005);
		hprof1_nhits_per_dtc_     ->GetXaxis()->SetLabelSize(0.005);
		hprof1_nstubs_per_dtc_    ->GetXaxis()->SetLabelSize(0.005);
		
		
		// Fill Hardware histograms
		for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
		{
			size_t const nModules = outerTrackerDTCCablingMapHandle_->cablingMapDTCIdToDetId_.count(dtc_ref);
			
			h1_nmodules_per_dtc_     ->Fill(dtc_ref.name(), nModules);
		}
		
		
		// Prepare bins in rate histograms
		std::vector<DTCId> sortedKnownDTCs(outerTrackerDTCCablingMapHandle_->knownDTCIds_.begin(),outerTrackerDTCCablingMapHandle_->knownDTCIds_.end());
		std::sort(sortedKnownDTCs.begin(), sortedKnownDTCs.end(), [&](DTCId const& lhs,DTCId const& rhs)
			{
				std::string const lhs_name(lhs.name());
				std::string const rhs_name(rhs.name());
				
				return std::lexicographical_compare(lhs_name.begin(), lhs_name.end(), rhs_name.begin(), rhs_name.end());
			}
		);
		
 		unsigned int iBin = 1;
 		for (auto const& dtc_ref : sortedKnownDTCs)
 		{
 			dtcBinningMap_.insert(std::make_pair<DTCId, unsigned int>(DTCId(dtc_ref), unsigned(iBin)));
 			++iBin;
 		}
		
		
		for (auto const& dtc_ref : sortedKnownDTCs)
		{
			hmax1_nhits_per_dtc_      ->Fill(dtc_ref.name(), 0.0);
			hmax1_nclusters_per_dtc_  ->Fill(dtc_ref.name(), 0.0);
			hmax1_nstubs_per_dtc_     ->Fill(dtc_ref.name(), 0.0);
			h2_daqrate_per_dtc_       ->Fill(dtc_ref.name(), 0.0, 0.0);
			h2_nhits_per_dtc_         ->Fill(dtc_ref.name(), 0.0, 0.0);
			h2_nclusters_per_dtc_     ->Fill(dtc_ref.name(), 0.0, 0.0);
			h2_nstubs_per_dtc_        ->Fill(dtc_ref.name(), 0.0, 0.0);
			hprof1_nhits_per_dtc_     ->Fill(dtc_ref.name(), 0.0, 0.0);
			hprof1_nclusters_per_dtc_ ->Fill(dtc_ref.name(), 0.0, 0.0);
			hprof1_nstubs_per_dtc_    ->Fill(dtc_ref.name(), 0.0, 0.0);
			
			max_nclusters_per_dtc_[dtc_ref] = 0;
			max_nhits_per_dtc_    [dtc_ref] = 0;
			max_nstubs_per_dtc_   [dtc_ref] = 0;
		}
	}
	
	
	//
	// Begin event loop part
	//
	
	// Reset counters
	std::unordered_map<DTCId, unsigned int> hitCounts;
	std::unordered_map<DTCId, unsigned int> cluCounts;
	std::unordered_map<DTCId, unsigned int> stuCounts;
	std::unordered_map<DTCId, double>       bitCounts;
	
	for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
	{
		hitCounts[dtc_ref] = 0;
		cluCounts[dtc_ref] = 0;
		stuCounts[dtc_ref] = 0;
		bitCounts[dtc_ref] = 0;
	}
	
	
	for (auto const& hit_detset: *hitsHandle)
	{
		DetId detidObject( hit_detset.detId() );
		uint32_t const detId = detidObject;
		
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& hitDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
			
			std::size_t const nhits = hit_detset.size();
			
			hitCounts[hitDTC] += nhits;
		}
		else
		{
			cout << "hit DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	
	for (auto const& clu_detset: *clusHandle)
	{
		std::size_t const nclus = clu_detset.size();
		
		DetId         detidObject( clu_detset.detId() );
		SiStripDetId  siStripDetIdObject( clu_detset.detId() );
		
		uint32_t const detId = detidObject;
		
		int bits = 0;

		DetId stackDetid = trackerTopoHandle->stack(detidObject);
		bool isPS = (trackerGeomHandle->getDetectorType(stackDetid)==TrackerGeometry::ModuleType::Ph2PSP);

		if ((siStripDetIdObject.subDetector()==SiStripDetId::SubDetector::TOB) || (siStripDetIdObject.subDetector()==SiStripDetId::SubDetector::TID))
		{
			if ( ( isPS) && ( trackerTopoHandle->isLower(detidObject)) ) bits = 21 * nclus + 32;
			if ( ( isPS) && (!trackerTopoHandle->isLower(detidObject)) ) bits = 24 * nclus + 32;
			if ( (!isPS) )                                   bits = 21 * nclus + 32;
		}
		
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& cluDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
			
			cluCounts[cluDTC] += nclus;
			bitCounts[cluDTC] += bits;
		}
		else
		{
			cout << "cluster DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	
	for (auto const& stu_detset: *stubHandle)
	{
		DetId         detidObject( stu_detset.detId() );
		SiStripDetId  siStripDetIdObject( stu_detset.detId() );
		
		uint32_t const detId = detidObject;
		
		
#if 0
		// Ignore stubs in Disk 2 Ring 1, Disk 4 Ring 4-5, Disk 5 Ring 4-6
		// https://indico.cern.ch/event/651638/contributions/2664172/attachments/1494597/2324969
		
		bool ignoreStubs = false;
		
		if (siStripDetIdObject.subDetector()==SiStripDetId::SubDetector::TID)
		{
			int disk = trackerTopoHandle->tidWheel(detidObject);
			int ring = trackerTopoHandle->tidRing(detidObject);
			
			if ( (disk == 2) && (ring == 1) ) ignoreStubs = true;
			if ( (disk == 4) && ( (ring >= 1) && (ring <= 2) ) ) ignoreStubs = true;
			if ( (disk == 5) && ( (ring >= 1) && (ring <= 3) ) ) ignoreStubs = true;
		}
#else
		bool ignoreStubs = false;
#endif
		
		
		if (outerTrackerDTCCablingMapHandle_->knowsDetId(detId))
		{
			DTCId const& stuDTC = outerTrackerDTCCablingMapHandle_->detIdToDTC(detId);
			
			std::size_t const nstubs = stu_detset.size();
			
			stuCounts[stuDTC] += nstubs;
		}
		else
		{
			cout << "stub DetId = " << detId << " ---> NO DTC IN MAP!" << endl;
		}
	}
	
	constexpr std::size_t const ndth = 19;
	
	//std::unordered_map<int, double> dthdatarate;
	std::array<double, ndth> dthdatarate;
	
	for (std::size_t i = 0; i < ndth; i++)
	{
	  dthdatarate[i] = 0.0;
	}
	
	// Fill the histograms
	for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
	{
		max_nclusters_per_dtc_[dtc_ref] = std::max(max_nclusters_per_dtc_[dtc_ref] , hitCounts[dtc_ref]);
		max_nhits_per_dtc_    [dtc_ref] = std::max(max_nhits_per_dtc_    [dtc_ref] , cluCounts[dtc_ref]);
		max_nstubs_per_dtc_   [dtc_ref] = std::max(max_nstubs_per_dtc_   [dtc_ref] , stuCounts[dtc_ref]);
		
		h2_nhits_per_dtc_     ->Fill(dtc_ref.name(), double(hitCounts[dtc_ref]), 1.0);
		h2_nclusters_per_dtc_ ->Fill(dtc_ref.name(), double(cluCounts[dtc_ref]), 1.0);
		h2_nstubs_per_dtc_    ->Fill(dtc_ref.name(), double(stuCounts[dtc_ref]), 1.0);
			
		hprof1_nhits_per_dtc_    ->Fill(dtc_ref.name(), double(hitCounts[dtc_ref]), 1.0);
		hprof1_nclusters_per_dtc_->Fill(dtc_ref.name(), double(cluCounts[dtc_ref]), 1.0);
		hprof1_nstubs_per_dtc_   ->Fill(dtc_ref.name(), double(stuCounts[dtc_ref]), 1.0);
		
		double const daqrate = (bitCounts[dtc_ref]+960000)/1000000;
		
		h2_daqrate_per_dtc_->Fill(dtc_ref.name(), daqrate, 1.0);
		
		if (strstr(dtc_ref.name(),"2S"))
		{
		  const char * pch = strstr (dtc_ref.name(),"_2S");
		  --pch;
		  dthdatarate[atoi(pch)+9] += daqrate;
		}
		else if (strstr(dtc_ref.name(),"PS"))
		{
		  const char * pch = strstr (dtc_ref.name(),"_PS");
		  --pch;
		  dthdatarate[atoi(pch)] += daqrate;
			
			if (strstr(dtc_ref.name(),"_PS10G_2")) {
				h1_nstubs_in_ps10g_2_->Fill(double(stuCounts[dtc_ref]));
			}
			if (strstr(dtc_ref.name(),"_PS10G_1")) {
				h1_nstubs_in_ps10g_1_->Fill(double(stuCounts[dtc_ref]));
			}
		}
	}
	
	for (std::size_t i = 0; i < ndth; i++)
	{
	  h2_daqrate_per_dth_->Fill(i,dthdatarate[i]);
	}
}

void DTCBandwidthStatisticsAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
	
}

void DTCBandwidthStatisticsAnalyzer::endJob() 
{
	for (auto const& dtc_ref : outerTrackerDTCCablingMapHandle_->knownDTCIds_)
	{
// 		hmax1_nclusters_per_dtc_ ->SetBinContent(dtcBinningMap_[dtc_ref], 0.0);
// 		hmax1_nhits_per_dtc_     ->SetBinContent(dtcBinningMap_[dtc_ref], 0.0);
// 		hmax1_nstubs_per_dtc_    ->SetBinContent(dtcBinningMap_[dtc_ref], 0.0);
		
		hmax1_nclusters_per_dtc_ ->Fill(dtc_ref.name(), max_nclusters_per_dtc_[dtc_ref]);
		hmax1_nhits_per_dtc_     ->Fill(dtc_ref.name(), max_nhits_per_dtc_    [dtc_ref]);
		hmax1_nstubs_per_dtc_    ->Fill(dtc_ref.name(), max_nstubs_per_dtc_   [dtc_ref]);
	}
}

DTCBandwidthStatisticsAnalyzer::~DTCBandwidthStatisticsAnalyzer()
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCBandwidthStatisticsAnalyzer);
