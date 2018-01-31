// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/Phase2TrackerDTC
// Class:      DTCCablingMapProducer
// 
/**\class DTCCablingMapProducer DTCCablingMapProducer.cc SLHCUpgradeSimulations/Phase2TrackerDTC/plugins/DTCCablingMapProducer.cc

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

#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"


class DTCCablingMapProducer : public edm::one::EDAnalyzer<>
{
	public:
			explicit DTCCablingMapProducer(const edm::ParameterSet&);
			~DTCCablingMapProducer();
			
			static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
			
			
	private:
			virtual void beginJob() override;
			virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
			virtual void endJob() override;
			
};


void DTCCablingMapProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DTCCablingMapProducer::DTCCablingMapProducer(const edm::ParameterSet& iConfig)
{
	
}


DTCCablingMapProducer::~DTCCablingMapProducer()
{
	
}


void DTCCablingMapProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
	
	OuterTrackerDTCCablingMap* pMyOuterTrackerDTCCablingMap = new OuterTrackerDTCCablingMap();
	
	pMyOuterTrackerDTCCablingMap->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(11111111, DTCId("2_2S_1")));
	pMyOuterTrackerDTCCablingMap->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(22222222, DTCId("2_2S_2")));
	pMyOuterTrackerDTCCablingMap->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(33333333, DTCId("2_2S_3")));
	pMyOuterTrackerDTCCablingMap->cablingMapDetToDTC_.insert(make_pair<uint32_t, DTCId>(44444444, DTCId("2_2S_3")));
	
	pMyOuterTrackerDTCCablingMap->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_1"), 11111111));
	pMyOuterTrackerDTCCablingMap->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_2"), 22222222));
	pMyOuterTrackerDTCCablingMap->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_3"), 33333333));
	pMyOuterTrackerDTCCablingMap->cablingMapDTCToDet_.insert(make_pair<DTCId, uint32_t>(DTCId("2_2S_3"), 44444444));
	
	edm::Service<cond::service::PoolDBOutputService> poolDbService;
	
	if( poolDbService.isAvailable() )
		poolDbService->writeOne( pMyOuterTrackerDTCCablingMap, poolDbService->currentTime(), "OuterTrackerDTCCablingMapRcd" );
	else
		throw std::runtime_error("PoolDBService required.");
	
}


// ------------ method called once each job just before starting event loop  ------------
void DTCCablingMapProducer::beginJob()
{
	
}

// ------------ method called once each job just after ending the event loop  ------------
void DTCCablingMapProducer::endJob() 
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCCablingMapProducer);
