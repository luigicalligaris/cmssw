// -*- C++ -*-
//
// Package:    SLHCUpgradeSimulations/DTCCablingMapProducer
// Class:      DTCCablingMapProducer
// 
/**\class DTCCablingMapProducer DTCCablingMapProducer.cc SLHCUpgradeSimulations/TrackerDTCPerformance/plugins/DTCCablingMapProducer.cc

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

#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/AssociationVector.h"


#include "DataFormats/DetId/interface/DetId.h"
#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/DTCId.h"

// needed for reading the cabling map ?
// #include "CondTools/​SiStrip/​plugins/​SiStripCablingTrackerMap.h"
// #include "CondTools/​SiStrip/​plugins/​SiStripFedCablingReader.h"




// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class DTCCablingMapProducer : public edm::one::EDProducer<edm::one::WatchRuns,edm::BeginRunProducer>
{
	public:
		explicit DTCCablingMapProducer(const edm::ParameterSet&);
		~DTCCablingMapProducer();
		
		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	private:
		virtual void beginJob() override;
		virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
		virtual void beginRunProduce(edm::Run&, edm::EventSetup const&) override;
// 		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&) override;
// 		virtual void beginLuminosityBlockProduce(edm::LuminosityBlock&, EventSetup const&) override;
		
		virtual void produce(edm::Event&, const edm::EventSetup&) override;
		
// 		virtual void endLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&) override;
// 		virtual void endLuminosityBlockProduce(edm::LuminosityBlock&, EventSetup const&) override;
		virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
// 		virtual void endRunProduce(edm::Run&, edm::EventSetup const&) override;
		virtual void endJob() override;
		
		void ReadCablingFromCSV(char const*);
	private:
		
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
	
	produces< std::vector< TrackerDTCPerformance::DTCId >,edm::InRun>().setBranchAlias("AllDTCs");
	produces< edm::AssociationMap< edm::OneToOne< std::vector<DetId>, std::vector<TrackerDTCPerformance::DTCId> > > >().setBranchAlias("TrackerModuleToDTCMap");
}

void DTCCablingMapProducer::beginJob()
{
	
}

void DTCCablingMapProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
	
}

void DTCCablingMapProducer::beginRunProduce(edm::Run&, edm::EventSetup const&)
{
	
}

// void beginLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&)
// {
// 	
// }
// 
// void beginLuminosityBlockProduce(edm::LuminosityBlock&, EventSetup const&)
// {
// 	
// }

void DTCCablingMapProducer::ReadCablingFromCSV(char const* csvFilePath)
{
	
}

void DTCCablingMapProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	
}

// void DTCCablingMapProducer::endLuminosityBlock(edm::LuminosityBlock const&, EventSetup const&)
// {
// 	
// }
// 
// void DTCCablingMapProducer::endLuminosityBlockProduce(edm::LuminosityBlock&, EventSetup const&)
// {
// 	
// }

void DTCCablingMapProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
	
}

// void DTCCablingMapProducer::endRunProduce(edm::Run&, edm::EventSetup const&)
// {
// 	
// }


void DTCCablingMapProducer::endJob() 
{
	
}

DTCCablingMapProducer::~DTCCablingMapProducer()
{
	
}

DEFINE_FWK_MODULE(DTCCablingMapProducer);
