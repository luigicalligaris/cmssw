#ifndef SLHCUpgradeSimulations_TrackerDTCPerformanceDataFormats_DTCId_h
#define SLHCUpgradeSimulations_TrackerDTCPerformanceDataFormats_DTCId_h

#include <string>

namespace TrackerDTCPerformance
{
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
		
		std::string name() const noexcept {return dtc_name_;}
		std::size_t hash() const noexcept {return dtc_name_hash_;}
		
		inline bool operator< (DTCId const& rhs) const noexcept {return dtc_name_hash_ <  rhs.dtc_name_hash_;}
		inline bool operator> (DTCId const& rhs) const noexcept {return dtc_name_hash_ >  rhs.dtc_name_hash_;}
		inline bool operator==(DTCId const& rhs) const noexcept {return dtc_name_hash_ == rhs.dtc_name_hash_ && dtc_name_ == rhs.dtc_name_;}
		inline bool operator!=(DTCId const& rhs) const noexcept {return dtc_name_hash_ != rhs.dtc_name_hash_ || dtc_name_ != rhs.dtc_name_;}
		
	private:
		std::size_t dtc_name_hash_;
		std::string dtc_name_;
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


#endif // end SLHCUpgradeSimulations_TrackerDTCPerformanceDataFormats_DTCId_hh
