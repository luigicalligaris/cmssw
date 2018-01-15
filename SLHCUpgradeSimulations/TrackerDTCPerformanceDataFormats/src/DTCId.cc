#include "SLHCUpgradeSimulations/TrackerDTCPerformance/interface/DTCId.hh"
#include "SLHCUpgradeSimulations/TrackerDTCPerformance/interface/Hash.hh"

#include <string>
#include <functional>

namespace TrackerDTCPerformance
{
	DTCId::DTCId(const char* dtc_id):
		dtc_id_     (dtc_id)
	{
		std::hash<std::string> string_hasher;
		dtc_id_hash_ = string_hasher(dtc_id_);
	}
	
	DTCId::~DTCId() {}
	
	DTCId::DTCId(DTCId const& rhs):
		dtc_id_     (rhs.dtc_id_),
		dtc_id_hash_(rhs.dtc_id_hash_)
	{}
	
	DTCId::DTCId(DTCId&& rhs):
		dtc_id_     (std::move(rhs.dtc_id_)),
		dtc_id_hash_(rhs.dtc_id_hash_)
	{}
	
	DTCId& DTCId::operator=(DTCId const& rhs)
	{
		dtc_id_      = rhs.dtc_id_;
		dtc_id_hash_ = rhs.dtc_id_hash_;
		return *this;
	}
	
	DTCId& DTCId::operator=(DTCId&& rhs)
	{
		dtc_id_      = std::move(rhs.dtc_id_);
		dtc_id_hash_ = rhs.dtc_id_hash_;
		return *this;
	}
	
	
	
	DTCId::DTCId(const std::string& rhs):
		dtc_id_     (rhs)
	{
		std::hash<std::string> string_hasher;
		dtc_id_hash_ = string_hasher(dtc_id_);
	}
	
	DTCId::DTCId(std::string&& rhs):
		dtc_id_     (rhs)
	{
		std::hash<std::string> string_hasher;
		dtc_id_hash_ = string_hasher(dtc_id_);
	}
	
	DTCId& DTCId::operator=(std::string const& rhs)
	{
		dtc_id_      = rhs;
		std::hash<std::string> string_hasher;
		dtc_id_hash_ = string_hasher(dtc_id_);
		return *this;
	}
	
	DTCId& DTCId::operator=(std::string&& rhs)
	{
		dtc_id_      = rhs;
		std::hash<std::string> string_hasher;
		dtc_id_hash_ = string_hasher(dtc_id_);
		return *this;
	}
}
