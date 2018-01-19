#ifndef SLHCUpgradeSimulations_TrackerDTCPerformance_DTCCablingMap_hh
#define SLHCUpgradeSimulations_TrackerDTCPerformance_DTCCablingMap_hh

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/DTCId.h"
#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/Common/interface/AssociationMap.h"
// #include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/Common/interface/OneToValue.h"
#include "DataFormats/Common/interface/OneToOne.h"
#include "DataFormats/Common/interface/OneToManyWithQuality.h"

namespace TrackerDTCPerformance
{
// 	enum ModuleType {2S,PS};
// 	
// 	struct DTCCablingMapRecord
// 	{
// 		ModuleType moduleType          ;
// 		uint32_t   moduleDetId         ;
// 		signed int moduleLayer         ;
// 		signed int moduleRing          ;
// 		signed int bundleNumber        ;
// 		signed int cableNumber         ;
// 		signed int cableServicesChannel;
// 		signed int dtcPhiSectorRef     ;
// 		signed int dtcSlot             ;
// 		
// 		double modulePhiDeg        ;
// 		double dtcPhiSectorWidthDeg;
// 		
// 		std::string moduleSection;
// 		std::string cableType    ;
// 		std::string dtcName      ;
// 		std::string dtcType      ;
// 	};
	
	class DTCCablingMap
	{
		public:
			DTCCablingMap(int const);
			~DTCCablingMap();
			
			void LoadCablingCSV(char const*);
			void ResetCablingMap();
			
		private:
			int printLevel_;
			
			std::unordered_set<DetId>                                                    allTrkDetIds_      ;
			std::unordered_map<DetId, bool>                                              isPSmodule_        ;
			std::unordered_map<DetId, TrackerDTCPerformance::DTCId>                      mapStackedDETtoDTC_;
			std::unordered_map<DetId, TrackerDTCPerformance::DTCId>                      mapDETtoDTC_       ;
			std::unordered_map<TrackerDTCPerformance::DTCId, std::unordered_set<DetId> > mapDTCtoDETS_      ;
	};
}

#endif // end SLHCUpgradeSimulations_TrackerDTCPerformance_DTCCablingMap_hh
