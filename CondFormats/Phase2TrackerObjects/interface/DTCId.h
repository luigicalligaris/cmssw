#ifndef DataFormats_Phase2TrackerDTC_DTCId_h
#define DataFormats_Phase2TrackerDTC_DTCId_h

#include <string>
#include "CondFormats/Serialization/interface/Serializable.h"

class DTCId
{
public:
	DTCId() noexcept;
	~DTCId() noexcept;
	
	DTCId(DTCId const& rhs) noexcept;
	DTCId(DTCId&& rhs) noexcept;
	DTCId& operator=(DTCId const& rhs) noexcept;
	DTCId& operator=(DTCId&& rhs) noexcept;
	
	DTCId(unsigned short const) noexcept;
	DTCId& operator=(unsigned short const) noexcept;
	
	inline bool operator< (DTCId const& rhs) const noexcept {return dtc_number_ <  rhs.dtc_number_;}
	inline bool operator> (DTCId const& rhs) const noexcept {return dtc_number_ >  rhs.dtc_number_;}
	inline bool operator==(DTCId const& rhs) const noexcept {return dtc_number_ == rhs.dtc_number_;}
	inline bool operator!=(DTCId const& rhs) const noexcept {return dtc_number_ != rhs.dtc_number_;}
	
	inline unsigned short dtc_number() const noexcept {return dtc_number_;}
	
private:
	unsigned short dtc_number_;
	
	COND_SERIALIZABLE;
};

namespace std
{
	template <>
	struct hash<DTCId>
	{
		size_t operator()(const DTCId& k) const noexcept
		{
			return k.dtc_number();
		}
	};
}


#endif // end DataFormats_Phase2TrackerDTC_DTCId_h

