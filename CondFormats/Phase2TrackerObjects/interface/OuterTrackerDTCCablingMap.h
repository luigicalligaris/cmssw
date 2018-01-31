#include <vector>
#include <unordered_map>
#include <cstdint>

#include "CondFormats/Serialization/interface/Serializable.h"
#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/DetId/interface/DetIdHash.h"

class OuterTrackerDTCCablingMap
{
	public:
		OuterTrackerDTCCablingMap();
		virtual ~OuterTrackerDTCCablingMap();
		
		std::unordered_map     <uint32_t, DTCId> cablingMapDetToDTC_;
		std::unordered_multimap<DTCId, uint32_t> cablingMapDTCToDet_;
		
		COND_SERIALIZABLE;
};

