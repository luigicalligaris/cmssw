#include "SLHCUpgradeSimulations/TrackerDTCPerformance/interface/DTCCablingMap.hh"
#include "SLHCUpgradeSimulations/TrackerDTCPerformance/interface/DTCId.hh"
#include "FWCore/Utilities/interface/Exception.h"

#include <vector>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace TrackerDTCPerformance
{
	DTCCablingMap::DTCCablingMap(int const printLevel = 0) : printLevel_(printLevel)
	{
		
	}
	
	DTCCablingMap::~DTCCablingMap()
	{
		
	}
	
	void DTCCablingMap::LoadCablingCSV(char const* cabling_csv_file_path)
	{
		using namespace std;
		
		ifstream csvFile;
		csvFile.open(cabling_csv_file_path);
		
		if (csvFile.is_open())
		{
			// Read the file line by line
			string csvLine;
			while (std::getline(csvFile, csvLine))
			{
				// Skip the legend
				if (std::string("Module") == csvLine.substr(0,6))
					continue;
				
				// We need a stringstream to manipulate the lines
				istringstream csvStream(csvLine);
				
				// Split the line in columns
				vector<string> csvColumn;
				string csvElement;
				while (std::getline(csvStream, csvElement, ','))
					csvColumn.push_back(csvElement);
				
				unsigned int detIdRaw;
				string dtcId;
				
				constexpr unsigned int const n_columns      = 14;
				constexpr unsigned int const i_column_detId =  0;
				
				
				if (csvColumn.size() == n_columns)
				{
					try
					{
						detIdRaw = std::stoi(csvColumn[i_column_detId]);
					}
					catch (std::exception e)
					{
						if (printLevel_ >= 3)
							cout << "Error parsing CSV file. The detId column string cannot be converted to an integer, skipped line: " << csvLine << endl;
						continue;
					}
					
					dtcId = csvColumn[9];
					
					if (printLevel_ >= 3)
						cout << "Reading CSV file: DetId = " << detIdRaw << " dtcId = " << dtcId << endl;
					
					// Create maps containing module - DTC cabling.
					mapStackedDETtoDTC_[ DetId(detIdRaw) ] = dtcId;
				}
				else 
				{
					if (printLevel_ >= 3)
						cout << "Error parsing CSV file. Wrong number of columns, skipped line: " << csvLine << endl;
				}
			}
		}
		else
		{
			throw cms::Exception("ClusterStudy: Unable to open input CSV file") << cabling_csv_file_path << endl;
		}
	}
	
	void DTCCablingMap::ResetCablingMap()
	{
		mapStackedDETtoDTC_.clear();
	}
}
