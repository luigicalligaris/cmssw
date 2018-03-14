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
	OuterTrackerDTCCablingMap::dtcToDetId(DTCId const& dtcId) const
{
	if (cablingMapDTCIdToDetId_.find(dtcId) == cablingMapDTCIdToDetId_.end())
	{
		throw cms::Exception("OuterTrackerDTCCablingMap has been asked to return a range of associated DetIds for a DTCId which is unknown. ")<<" DTC name = " << dtcId.name() << std::endl;
	}
	
	return cablingMapDTCIdToDetId_.equal_range(dtcId);
}


DTCId const& OuterTrackerDTCCablingMap::detIdToDTC(uint32_t detId) const
{
	if (cablingMapDetIdToDTCIdIndex_.find(detId) == cablingMapDetIdToDTCIdIndex_.end())
	{
		throw cms::Exception("OuterTrackerDTCCablingMap has been asked to return a DTCId associated to a DetId which is unknown. ")<<" DetId = " << detId << std::endl;
	}
	
	std::size_t const dtcIndex = cablingMapDetIdToDTCIdIndex_.at(detId);
	return knownDTCIds_[dtcIndex];
}


bool OuterTrackerDTCCablingMap::knowsDTCId(DTCId const& dtcId) const
{
	return cablingMapDTCIdToDetId_.find(dtcId) != cablingMapDTCIdToDetId_.end();
}


bool OuterTrackerDTCCablingMap::knowsDetId(uint32_t detId) const
{
	return cablingMapDetIdToDTCIdIndex_.find(detId) != cablingMapDetIdToDTCIdIndex_.end();
}


void OuterTrackerDTCCablingMap::insert(DTCId const& dtcId, uint32_t detId)
{
	if (cablingMapDTCIdToDetId_.find(dtcId) != cablingMapDTCIdToDetId_.end())
	{
		cablingMapDTCIdToDetId_.insert(std::make_pair(DTCId(dtcId), uint32_t(detId)));
		
		
		std::vector<DTCId>::iterator const dtcIdIter = std::find(knownDTCIds_.begin(), knownDTCIds_.end(), dtcId);
		
		uint32_t const dtcIndex(dtcIdIter - knownDTCIds_.begin());
		cablingMapDetIdToDTCIdIndex_.insert(std::make_pair(uint32_t(detId), uint32_t(dtcIndex)));
	}
	else
	{
		cablingMapDTCIdToDetId_.insert(std::make_pair(DTCId(dtcId), uint32_t(detId)));
		
		std::size_t const dtcIndex(knownDTCIds_.size());
		knownDTCIds_.push_back(dtcId);
		cablingMapDetIdToDTCIdIndex_.insert(std::make_pair(uint32_t(detId), uint32_t(dtcIndex)));
	}
}


void OuterTrackerDTCCablingMap::clear()
{
	knownDTCIds_.clear();
	cablingMapDTCIdToDetId_.clear();
	cablingMapDetIdToDTCIdIndex_.clear();
}
