// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/ClusterDTCMapProducer
// Class:      ClusterDTCMapProducer
// 
/**\class ClusterDTCMapProducer ClusterDTCMapProducer.cc SLHCUpgradeSimulations/TrackerDTCPerformance/plugins/ClusterDTCMapProducer.cc

Description: EDProducer that produces an association map of the DTC a tracker cluster is associated to and, vice-versa, an association map of clusters associated with a specific DTC

Implementation:
		[Notes on implementation]
*/
//
// Original Author:  Luigi Calligaris (SPRACE, São Paulo, BR)
//         Created:  Thu, 14 Dec 2017 20:43:49 GMT
//
//


#include <memory>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDProducer.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


// needed for reading the cabling map ?
#include "CondTools/​SiStrip/​plugins/​SiStripCablingTrackerMap.h"
#include "CondTools/​SiStrip/​plugins/​SiStripFedCablingReader.h"




// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class ClusterDTCMapProducer : public edm::one::EDProducer  {
	public:
		explicit ClusterDTCMapProducer(const edm::ParameterSet&);
		~ClusterDTCMapProducer();
		
		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	private:
		virtual void beginJob() override;
		virtual void beginRun(edm::Run const &, edm::EventSetup const &) override;
		virtual void beginLuminosityBlock(LuminosityBlock const &, EventSetup const &) override;
		
		virtual void produce(edm::Event&, const edm::EventSetup&) override;
		
		virtual void endLuminosityBlock() override;
		virtual void endRun() override;
		virtual void endJob() override;
		
	private:
		
};

ClusterDTCMapProducer::ClusterDTCMapProducer(const edm::ParameterSet& iConfig)
{
	
}


ClusterDTCMapProducer::~ClusterDTCMapProducer()
{
	
}

void ClusterDTCMapProducer::produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	
}

void ClusterDTCMapProducer::beginJob()
{
	
}

void ClusterDTCMapProducer::endJob() 
{
	
}

void ClusterDTCMapProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(ClusterDTCMapProducer);
