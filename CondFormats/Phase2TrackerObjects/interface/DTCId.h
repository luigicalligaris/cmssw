#ifndef DataFormats_Phase2TrackerDTC_DTCId_h
#define DataFormats_Phase2TrackerDTC_DTCId_h

#include <string>
#include "CondFormats/Serialization/interface/Serializable.h"

class DTCId
{
public:
	DTCId();
	~DTCId();
	
	DTCId(DTCId const& rhs);
	DTCId(DTCId&& rhs);
	DTCId& operator=(DTCId const& rhs);
	DTCId& operator=(DTCId&& rhs);
	
	DTCId(char const*);
	DTCId& operator=(char const*);
	
	DTCId(std::string const&);
	DTCId(std::string&&);
	DTCId& operator=(std::string const&);
	DTCId& operator=(std::string&&);
	
	inline std::string name() const noexcept {return dtc_name_;}
	inline std::size_t hash() const noexcept {return dtc_name_hash_;}
	
	inline bool operator< (DTCId const& rhs) const noexcept {return dtc_name_hash_ <  rhs.dtc_name_hash_;}
	inline bool operator> (DTCId const& rhs) const noexcept {return dtc_name_hash_ >  rhs.dtc_name_hash_;}
	inline bool operator==(DTCId const& rhs) const noexcept {return dtc_name_hash_ == rhs.dtc_name_hash_ && dtc_name_ == rhs.dtc_name_;}
	inline bool operator!=(DTCId const& rhs) const noexcept {return dtc_name_hash_ != rhs.dtc_name_hash_ || dtc_name_ != rhs.dtc_name_;}
	
private:
	std::size_t dtc_name_hash_;
	std::string dtc_name_;
	
	COND_SERIALIZABLE;
};

namespace std
{
	template <>
	struct hash<DTCId>
	{
		size_t operator()(const DTCId& k) const
		{
			return k.hash();
		}
	};
}


#endif // end DataFormats_Phase2TrackerDTC_DTCId_h

