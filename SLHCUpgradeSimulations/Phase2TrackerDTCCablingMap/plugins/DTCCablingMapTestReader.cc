// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/Phase2TrackerDTC
// Class:      DTCCablingMapTestReader
// 
/**\class DTCCablingMapTestReader DTCCablingMapTestReader.cc SLHCUpgradeSimulations/Phase2TrackerDTC/plugins/DTCCablingMapTestReader.cc

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


#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondFormats/Phase2TrackerObjects/interface/OuterTrackerDTCCablingMap.h"
#include "CondFormats/DataRecord/interface/OuterTrackerDTCCablingMapRcd.h"


class DTCCablingMapTestReader : public edm::one::EDAnalyzer<>
{
	public:
			explicit DTCCablingMapTestReader(const edm::ParameterSet&);
			~DTCCablingMapTestReader();
			
			static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
			
			
	private:
			virtual void beginJob() override;
			virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
			virtual void endJob() override;
			
};


void DTCCablingMapTestReader::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DTCCablingMapTestReader::DTCCablingMapTestReader(const edm::ParameterSet& iConfig)
{
	
}


DTCCablingMapTestReader::~DTCCablingMapTestReader()
{
	
}


void DTCCablingMapTestReader::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
	
	edm::ESHandle<OuterTrackerDTCCablingMap> outerTrackerDTCCablingMapHandle;
	iSetup.get<OuterTrackerDTCCablingMapRcd>().get( outerTrackerDTCCablingMapHandle );
	OuterTrackerDTCCablingMap const* p_outerTrackerDTCCablingMap = outerTrackerDTCCablingMapHandle.product();
	
	{
		cout << "Det To DTC map elements dump (Python-style):" << endl;
		std::vector<uint32_t> const knownDetIds = p_outerTrackerDTCCablingMap->getKnownDetIds();
		
		cout << "{";
		for (uint32_t detId : knownDetIds)
		{
			DTCId const associatedDTC = p_outerTrackerDTCCablingMap->detIdToDTCId(detId);
			cout << detId << " : " << associatedDTC.dtc_number() << ", ";
		}
		cout << "}" << endl;
	}
	
	{
		cout << "DTC To Det map elements dump (Python-style):" << endl;
		std::vector<DTCId> const knownDTCIds = p_outerTrackerDTCCablingMap->getKnownDTCIds();
		
		cout << "{";
		for (DTCId currentDTC : knownDTCIds)
		{
			cout << currentDTC.dtc_number() << " : [";
			auto equal_range = p_outerTrackerDTCCablingMap->dtcIdToDetId(currentDTC);
			
			for (auto it = equal_range.first; it != equal_range.second; ++it)
				cout << it->second << ", ";
			
			cout << "], ";
		}
		cout << "}" << endl;
	}
}


// ------------ method called once each job just before starting event loop  ------------
void DTCCablingMapTestReader::beginJob()
{
	
}

// ------------ method called once each job just after ending the event loop  ------------
void DTCCablingMapTestReader::endJob() 
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCCablingMapTestReader);
