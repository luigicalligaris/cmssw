#include "CondFormats/Phase2TrackerObjects/interface/OuterTrackerDTCCablingMap.h"
#include "FWCore/Utilities/interface/Exception.h"

#include <algorithm>
#include <utility>

OuterTrackerDTCCablingMap::OuterTrackerDTCCablingMap()
{
	
}

OuterTrackerDTCCablingMap::~OuterTrackerDTCCablingMap()
{
	
}


std::pair<std::unordered_multimap<DTCId, uint32_t>::const_iterator, std::unordered_multimap<DTCId, uint32_t>::const_iterator>
	OuterTrackerDTCCablingMap::dtcIdToDetId(DTCId const dtcId) const
{
	if (cablingMapDTCIdToDetId_.find(dtcId) == cablingMapDTCIdToDetId_.end())
	{
		throw cms::Exception("OuterTrackerDTCCablingMap has been asked to return a range of associated DetIds for a DTCId which is unknown. ")<<" DTC number = " << dtcId.dtc_number() << std::endl;
	}
	
	return cablingMapDTCIdToDetId_.equal_range(dtcId);
}


DTCId OuterTrackerDTCCablingMap::detIdToDTCId(uint32_t const detId) const
{
	auto const DTCId_it = cablingMapDetIdToDTCId_.find(detId);
	
	if (DTCId_it == cablingMapDetIdToDTCId_.end())
	{
		throw cms::Exception("OuterTrackerDTCCablingMap has been asked to return a DTCId associated to a DetId which is unknown. ")<<" DetId = " << detId << std::endl;
	}
	
	return DTCId_it->second;
}


bool OuterTrackerDTCCablingMap::knowsDTCId(DTCId const& dtcId) const
{
	return cablingMapDTCIdToDetId_.find(dtcId) != cablingMapDTCIdToDetId_.end();
}

bool OuterTrackerDTCCablingMap::knowsDetId(uint32_t detId) const
{
	return cablingMapDetIdToDTCId_.find(detId) != cablingMapDetIdToDTCId_.end();
}


void OuterTrackerDTCCablingMap::insert(DTCId const& dtcId, uint32_t const detId)
{
	cablingMapDTCIdToDetId_.insert(std::make_pair(DTCId(dtcId), uint32_t(detId)));
	cablingMapDetIdToDTCId_.insert(std::make_pair(uint32_t(detId), DTCId(dtcId)));
}


std::vector<DTCId>    OuterTrackerDTCCablingMap::getKnownDTCIds() const
{
	std::vector<DTCId> knownDTCIds;
	
	// To get the list of unique DTCIds we need to iterate over the various equal_ranges 
	// in the map associated to each unique key, and count them only once.
	// 
	// (1,1204154577) --> Save only this "1", avoiding quadruple-counting
	// (1,1855483346) --> Skip
	// (1,1898825165) --> Skip
	// (1,2452144599) --> Skip
	// (2,1688475925) --> Save only this "2", avoiding double-counting
	// (2,8469300953) --> Skip
	// (3,2109104948) --> Save only this "3", avoiding triple-counting
	// (3,5611587006) --> Skip
	// (3,3460273485) --> Skip
	
	for (auto allpairs_it = cablingMapDTCIdToDetId_.begin(), allpairs_end = cablingMapDTCIdToDetId_.end(); allpairs_it != allpairs_end; )
	{
		// ***Store the first instance of the key***
		knownDTCIds.push_back(allpairs_it->first);
		
		// *** Skip to the end of the equal range ***
		// The following is just explicative, the bottom expression is equivalent
		//auto const current_key             = allpairs_it->first;
		//auto const current_key_equal_range = cablingMapDTCIdToDetId_.equal_range(current_key);
		//auto const current_key_range_end   = current_key_equal_range.second;
		auto const current_key_range_end = cablingMapDTCIdToDetId_.equal_range(allpairs_it->first).second;
		
		while (allpairs_it != current_key_range_end)
			++allpairs_it;
	}
	
	return knownDTCIds;
}

std::vector<uint32_t> OuterTrackerDTCCablingMap::getKnownDetIds() const
{
	std::vector<uint32_t> knownDetId(cablingMapDetIdToDTCId_.size());
	
	// Unzip the map into a vector of DetIds, discarding the DTCIds
	std::transform(cablingMapDetIdToDTCId_.begin(), cablingMapDetIdToDTCId_.end(), knownDetId.begin(), [](auto pair){return pair.first;});
	
	return knownDetId;
}



void OuterTrackerDTCCablingMap::clear()
{
	cablingMapDTCIdToDetId_.clear();
	cablingMapDetIdToDTCId_.clear();
}
