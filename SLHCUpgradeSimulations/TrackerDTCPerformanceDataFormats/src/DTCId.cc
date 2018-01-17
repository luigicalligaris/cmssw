#include "SLHCUpgradeSimulations/TrackerDTCPerformanceDataFormats/interface/DTCId.h"

#include <string>
#include <functional>

namespace TrackerDTCPerformance
{
	DTCId::DTCId(const char* dtc_name):
		dtc_name_     (dtc_name)
	{
		std::hash<std::string> string_hasher;
		dtc_name_hash_ = string_hasher(dtc_name_);
	}
	
	DTCId::~DTCId() {}
	
	DTCId::DTCId(DTCId const& rhs):
		dtc_name_hash_(rhs.dtc_name_hash_),
		dtc_name_     (rhs.dtc_name_)
	{}
	
	DTCId::DTCId(DTCId&& rhs):
		dtc_name_hash_(rhs.dtc_name_hash_),
		dtc_name_     (rhs.dtc_name_)
	{}
	
	DTCId& DTCId::operator=(DTCId const& rhs)
	{
		dtc_name_hash_ = rhs.dtc_name_hash_;
		dtc_name_      = rhs.dtc_name_;
		return *this;
	}
	
	DTCId& DTCId::operator=(DTCId&& rhs)
	{
		dtc_name_hash_ = rhs.dtc_name_hash_;
		dtc_name_      = rhs.dtc_name_;
		return *this;
	}
	
	
	
	DTCId::DTCId(const std::string& dtc_name):
		dtc_name_     (dtc_name)
	{
		std::hash<std::string> string_hasher;
		dtc_name_hash_ = string_hasher(dtc_name_);
	}
	
	DTCId::DTCId(std::string&& dtc_name):
		dtc_name_     (dtc_name)
	{
		std::hash<std::string> string_hasher;
		dtc_name_hash_ = string_hasher(dtc_name_);
	}
	
	DTCId& DTCId::operator=(std::string const& dtc_name)
	{
		std::hash<std::string> string_hasher;
		dtc_name_hash_ = string_hasher(dtc_name);
		dtc_name_      = dtc_name;
		return *this;
	}
	
	DTCId& DTCId::operator=(std::string&& dtc_name)
	{
		std::hash<std::string> string_hasher;
		dtc_name_hash_ = string_hasher(dtc_name);
		dtc_name_      = dtc_name;
		return *this;
	}
}
