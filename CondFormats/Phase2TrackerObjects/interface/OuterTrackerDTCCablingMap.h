// -*- C++ -*-
//
// Package:    CondFormats/OuterTrackerDTCCablingMap
// Class:      OuterTrackerDTCCablingMap
// 
/**\class OuterTrackerDTCCablingMap OuterTrackerDTCCablingMap.cc CondFormats/OuterTrackerDTCCablingMap/src/OuterTrackerDTCCablingMap.cc

Description: Map associating DTCIds of Phase2 tracker DTCs to DetId of the sensors connected to each of them. The class uses a vector to store known DTCId, in order not to duplicate them for different detectors (the index is cheaper than the string), saving half the space it would use otherwise.

Implementation:
		[Notes on implementation]
*/
//
// Original Author:  Luigi Calligaris, SPRACE, São Paulo, BR
//         Created:  Tue, 30 Jan 2018 13:28:49 GMT
//
//

#include <vector>
#include <unordered_map>
#include <cstdint>

#include "CondFormats/Serialization/interface/Serializable.h"
#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"
#include "DataFormats/DetId/interface/DetId.h"

class OuterTrackerDTCCablingMap
{
	public:
		OuterTrackerDTCCablingMap();
		virtual ~OuterTrackerDTCCablingMap();
		
		std::pair<std::unordered_multimap<DTCId, uint32_t>::const_iterator, std::unordered_multimap<DTCId, uint32_t>::const_iterator> 
			dtcIdToDetId(DTCId const) const;
		
		DTCId detIdToDTCId(uint32_t) const;
		
		bool knowsDTCId(DTCId const&) const;
		bool knowsDetId(uint32_t) const;
		
		void insert(DTCId const&, uint32_t const);
		
		// IMPORTANT: The following information is not stored, to preserve space in memory.
		// As these vectors are generated each time the functions are called, you are encouraged to 
		// either cache the results or avoid calling them in hot loops.
		// NOTE: This vectors are unsorted
		std::vector<DTCId>    getKnownDTCIds() const;
		std::vector<uint32_t> getKnownDetIds() const;
		
		void clear();
		
	private:
		std::unordered_map     <uint32_t, DTCId> cablingMapDetIdToDTCId_;
		std::unordered_multimap<DTCId, uint32_t> cablingMapDTCIdToDetId_;
		
		COND_SERIALIZABLE;
};

