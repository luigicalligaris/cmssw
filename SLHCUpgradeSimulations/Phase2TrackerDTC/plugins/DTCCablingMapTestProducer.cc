// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/Phase2TrackerDTC
// Class:      DTCCablingMapTestProducer
// 
/**\class DTCCablingMapTestProducer DTCCablingMapTestProducer.cc SLHCUpgradeSimulations/Phase2TrackerDTC/plugins/DTCCablingMapTestProducer.cc

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
#include <unordered_map>
#include <utility>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondFormats/Phase2TrackerObjects/interface/OuterTrackerDTCCablingMap.h"
#include "CondFormats/DataRecord/interface/OuterTrackerDTCCablingMapRcd.h"
#include "CondFormats/Common/interface/Time.h"

#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"


class DTCCablingMapTestProducer : public edm::one::EDAnalyzer<>
{
	public:
		explicit DTCCablingMapTestProducer(const edm::ParameterSet&);
		~DTCCablingMapTestProducer();
		
		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
		
		
	private:
		virtual void beginJob() override;
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
		virtual void endJob() override;
private:
		cond::Time_t iovBeginTime_;
		std::string  recordName_;
};

void DTCCablingMapTestProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	edm::ParameterSetDescription desc;
	desc.setComment("Stores a OuterTrackerDTCCablingMap database object from a CSV file.");
  desc.add<long long unsigned int>("iovBeginTime", 1);
  desc.add<std::string>("record","OuterTrackerDTCCablingMapRcd");
	descriptions.addDefault(desc);
}

DTCCablingMapTestProducer::DTCCablingMapTestProducer(const edm::ParameterSet& iConfig):
	iovBeginTime_(iConfig.getParameter<long long unsigned int>("iovBeginTime")),
	recordName_  (iConfig.getParameter<std::string>("record"))
{
	
}

void DTCCablingMapTestProducer::beginJob()
{
	using namespace edm;
	using namespace std;
	
	OuterTrackerDTCCablingMap* pOuterTrackerDTCCablingMap_ = new OuterTrackerDTCCablingMap();
	
	pOuterTrackerDTCCablingMap_->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(11111111, DTCId("2_2S_1")));
	pOuterTrackerDTCCablingMap_->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(22222222, DTCId("2_2S_2")));
	pOuterTrackerDTCCablingMap_->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(33333333, DTCId("2_2S_3")));
	pOuterTrackerDTCCablingMap_->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(44444444, DTCId("2_2S_3")));
	
	pOuterTrackerDTCCablingMap_->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_1"), 11111111));
	pOuterTrackerDTCCablingMap_->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_2"), 22222222));
	pOuterTrackerDTCCablingMap_->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_3"), 33333333));
	pOuterTrackerDTCCablingMap_->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_3"), 44444444));
	
	edm::Service<cond::service::PoolDBOutputService> poolDbService;
	
	if( poolDbService.isAvailable() )
// 		poolDbService->writeOne( pOuterTrackerDTCCablingMap_, poolDbService->currentTime(), "OuterTrackerDTCCablingMapRcd" );
		poolDbService->writeOne( pOuterTrackerDTCCablingMap_, iovBeginTime_, recordName_ );
	else
		throw std::runtime_error("PoolDBService required.");
}


void DTCCablingMapTestProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	
}

void DTCCablingMapTestProducer::endJob() 
{
	
}

DTCCablingMapTestProducer::~DTCCablingMapTestProducer()
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCCablingMapTestProducer);
