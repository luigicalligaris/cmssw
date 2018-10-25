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
#include <cstdint>
#include <atomic>
#include <unordered_map>
#include <utility>

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
#include "CondFormats/Common/interface/Time.h"

#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/PixelTopology.h"





// trim from start (in place)
static inline void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
	{
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
	{
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
	trim(s);
	return s;
}





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
		
		virtual void LoadModulesToDTCCablingMapFromCSV(std::vector<std::string> const&);
		
	private:
		int          verbosity_;
		unsigned     csvFormat_ncolumns_;
		unsigned     csvFormat_idetid_  ;
		unsigned     csvFormat_idtcid_  ;
		cond::Time_t iovBeginTime_;
		std::string  record_;
		OuterTrackerDTCCablingMap* pOuterTrackerDTCCablingMap_;
};


void DTCCablingMapProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
	edm::ParameterSetDescription desc;
	desc.setComment("Stores a OuterTrackerDTCCablingMap database object from a CSV file.");
	desc.add<int>("verbosity", 0);
	desc.add<unsigned>("csvFormat_ncolumns", 15);
	desc.add<unsigned>("csvFormat_idetid"  ,  0);
	desc.add<unsigned>("csvFormat_idtcid"  , 10);
  desc.add<long long unsigned int>("iovBeginTime", 1);
  desc.add<std::string>("record","OuterTrackerDTCCablingMapRcd");
	desc.add<std::vector<std::string>>("modulesToDTCCablingCSVFileNames",std::vector<std::string>());
	descriptions.addDefault(desc);
}

DTCCablingMapProducer::DTCCablingMapProducer(const edm::ParameterSet& iConfig):
	verbosity_          (iConfig.getParameter<int>("verbosity")),
	csvFormat_ncolumns_ (iConfig.getParameter<unsigned>("csvFormat_ncolumns")),
	csvFormat_idetid_   (iConfig.getParameter<unsigned>("csvFormat_idetid"  )),
	csvFormat_idtcid_   (iConfig.getParameter<unsigned>("csvFormat_idtcid"  )),
	iovBeginTime_       (iConfig.getParameter<long long unsigned int>("iovBeginTime")),
	record_             (iConfig.getParameter<std::string>("record")),
	pOuterTrackerDTCCablingMap_(new OuterTrackerDTCCablingMap())
{
	LoadModulesToDTCCablingMapFromCSV(iConfig.getParameter<std::vector<std::string>>("modulesToDTCCablingCSVFileNames"));
}

void DTCCablingMapProducer::beginJob()
{
	
}

void DTCCablingMapProducer::LoadModulesToDTCCablingMapFromCSV(std::vector<std::string> const& modulesToDTCCablingCSVFileNames)
{
// 	std::vector<std::string>
// 	edm::FileInPath
// 	iConfig.getParameter<edm::FileInPath>("inputCablingFileName").fullPath().c_str()
	
	using namespace std;
	
	for (std::string const& csvFileName : modulesToDTCCablingCSVFileNames)
	{
		edm::FileInPath csvFilePath(csvFileName);
		
		ifstream csvFile;
		csvFile.open(csvFilePath.fullPath().c_str());
		
		if (csvFile.is_open())
		{
			string csvLine;
			
			unsigned lineNumber = 0;
			
			while (std::getline(csvFile, csvLine))
			{
				if (verbosity_ >= 1)
				{
					cout << "Reading CSV file line: " << ++lineNumber << ": \"" << csvLine << "\"" << endl;
				}
				
				istringstream csvStream(csvLine);
				vector<string> csvColumn;
				string csvElement;
				
				while (std::getline(csvStream, csvElement, ','))
				{
					trim(csvElement);
					csvColumn.push_back(csvElement);
				}
				
				if (verbosity_ >= 2)
				{
					cout << "-- split line is: [";
					
					for (string const& s : csvColumn)
						cout << "\"" << s << "\", ";
					
					cout << "]" << endl;
				}
				
				if (csvColumn.size() == csvFormat_ncolumns_)
				{
					// Skip the legend lines
					if (0 == csvColumn[0].compare(std::string("Module DetId/U")))
					{
						if (verbosity_ >= 1)
						{
							cout << "-- skipping as it is a legend line" << endl;
						}
						continue;
					}
					
					uint32_t detIdRaw;
					
					try
					{
						detIdRaw = std::stoi( csvColumn[csvFormat_idetid_] );
					}
					catch (std::exception e)
					{
						if (verbosity_ >= 0)
						{
							cout << "-- malformed DetId string in CSV file: \"" << csvLine << "\"" << endl;
						}
						throw e;
					}
					
					unsigned short const dtc_number = strtoul(csvColumn[csvFormat_idtcid_].c_str(), nullptr, 10);
					DTCId dtcId( dtc_number );
					
					if (verbosity_ >= 3)
					{
						cout << "-- DetId = " << detIdRaw << " dtcId = " << dtcId.dtc_number() << endl;
					}
					
					{
						if (pOuterTrackerDTCCablingMap_->knowsDetId(detIdRaw))
						{
							throw cms::Exception("Reading CSV file: CRITICAL ERROR, duplicated DetId entry about DetId = ") << detIdRaw << endl;
						}
					}
					
					pOuterTrackerDTCCablingMap_->insert(dtcId, detIdRaw);
				}
				else
				{
					if (verbosity_ >= 3)
					{
						cout << "Reading CSV file: Skipped a short line: \"" << csvLine << "\"" << endl;
					}
				}
			}
		}
		else
		{
			throw cms::Exception("DTCCablingMapESProducer: Unable to open input CSV file") << csvFilePath << endl;
		}
		
		csvFile.close();
	}
}

void DTCCablingMapProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
	
	bool firstEvent = true;
	
	if (firstEvent)
	{
		firstEvent = false;
		
		edm::ESHandle<TrackerGeometry> trackerGeometryHandle;
		edm::ESHandle<TrackerTopology> trackerTopologyHandle;
		
		iSetup.get<TrackerDigiGeometryRecord>().get(trackerGeometryHandle);
		iSetup.get<TrackerTopologyRcd       >().get(trackerTopologyHandle);
		
		
		// Get list of all silicon modules in tracker and select the ones in the OT.
		// As the XML DTC cabling map is in terms of DetId of module stacks, get from 
		// geometry all the modules, and associate them to DTCs through their stack DetId 
		// in the already loaded cabling map.
		
		for (const GeomDet* gd : trackerGeometryHandle->dets())
		{
			DetId const detId = gd->geographicalId();
			
			// Phase 2 Outer Tracker uses TOB code for entire barrel and TID code for entire endcap.
			if (detId.subdetId() != StripSubdetector::TOB && detId.subdetId() != StripSubdetector::TID)
				continue;
			
			DetId const stackId = trackerTopologyHandle->stack(detId);
			
			// While I could not find documentation on that, these values seems to be invalid
			if (stackId.null())
				continue;
			
			uint32_t const rawDetId  (detId  );
			uint32_t const rawStackId(stackId);
			
			if (pOuterTrackerDTCCablingMap_->knowsDetId(rawStackId))
			{
				
				DTCId const & dtcId = pOuterTrackerDTCCablingMap_->detIdToDTCId(rawStackId);
				
				pOuterTrackerDTCCablingMap_->insert(dtcId, rawDetId);
			}
			else
			{
				cerr << "Warning: the OuterTrackerDTCCablingMap does not know stack detId " << rawStackId << ", check if the cabling map has been loaded correctly " << rawStackId << endl;
			}
		}
	}
}

void DTCCablingMapProducer::endJob() 
{
	using namespace edm;
	using namespace std;
	
	edm::Service<cond::service::PoolDBOutputService> poolDbService;
	
	if( poolDbService.isAvailable() )
	{
// 		poolDbService->writeOne( pOuterTrackerDTCCablingMap_, poolDbService->currentTime(), "OuterTrackerDTCCablingMapRcd" );
		poolDbService->writeOne( pOuterTrackerDTCCablingMap_, iovBeginTime_, record_ );
	}
	else
	{
		throw cms::Exception("PoolDBService required.");
	}
}

DTCCablingMapProducer::~DTCCablingMapProducer()
{
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTCCablingMapProducer);
