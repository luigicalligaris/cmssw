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
		
		std::pair<unsigned int, DTCId> unorderedMapUIntToDTC_data = std::make_pair<unsigned int, DTCId>(0,DTCId("DICT_DUMMY"));
		std::pair<DTCId, unsigned int> unorderedMapDTCToUInt_data = std::make_pair<DTCId, unsigned int>(DTCId("DICT_DUMMY"),0);
	};
}

