#include "CondFormats/Phase2TrackerObjects/interface/OuterTrackerDTCCablingMap.h"
#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/DetId/interface/DetIdHash.h"

namespace
{
	struct dictionary
	{
		OuterTrackerDTCCablingMap cabmap;
		
		DTCId dtcid;
		
		std::unordered_map     <unsigned int, DTCId> unorderedMapUIntToDTC;
		std::unordered_multimap<DTCId, unsigned int> unorderedMapDTCToUInt;
		
		std::unordered_map     <DetId, DTCId> unorderedMapDetIdToDTC;
		std::unordered_multimap<DTCId, DetId> unorderedMapDTCToDetId;
	};
}

