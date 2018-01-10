#ifndef SLHCUpgradeSimulations_TrackerDTCPerformance_DTCId_hh
#define SLHCUpgradeSimulations_TrackerDTCPerformance_DTCId_hh

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "SLHCUpgradeSimulations/TrackerDTCPerformance/interface/Hash.hh"

namespace TrackerDTCPerformance
{
	typedef unsigned int ModuleId;
	typedef unsigned int LayerId;
	typedef unsigned int OctantId;
	
	class DTCId
	{
	public:
		DTCId(const char* dtc_id = "");
		~DTCId();
		
		DTCId(DTCId const& rhs);
		DTCId(DTCId&& rhs);
		DTCId& operator=(DTCId const& rhs);
		DTCId& operator=(DTCId&& rhs);
		
		DTCId(std::string const& rhs);
		DTCId(std::string&& rhs);
		DTCId& operator=(std::string const& rhs);
		DTCId& operator=(std::string&& rhs);
		
		std::string id()   const noexcept {return dtc_id_;}
		std::size_t hash() const noexcept {return dtc_id_hash_;}
		
		bool operator< (DTCId const& rhs) const noexcept {return dtc_id_hash_ <  rhs.dtc_id_hash_;}
		bool operator> (DTCId const& rhs) const noexcept {return dtc_id_hash_ >  rhs.dtc_id_hash_;}
		bool operator==(DTCId const& rhs) const noexcept {return dtc_id_hash_ ==  rhs.dtc_id_hash_ && dtc_id_ == rhs.dtc_id_;}
		bool operator!=(DTCId const& rhs) const noexcept {return dtc_id_hash_ !=  rhs.dtc_id_hash_ || dtc_id_ != rhs.dtc_id_;}
		
	private:
		std::string dtc_id_;
		std::size_t dtc_id_hash_;
	};
	
}

namespace std
{
	template <>
	struct hash<TrackerDTCPerformance::DTCId>
	{
		size_t operator()(const TrackerDTCPerformance::DTCId& k) const
		{
			return k.hash();
		}
	};
}


#endif // end SLHCUpgradeSimulations_TrackerDTCPerformance_DTCId_hh
