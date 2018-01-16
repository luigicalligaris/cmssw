#ifndef SLHCUpgradeSimulations_TrackerDTCPerformance_Hash_hh
#define SLHCUpgradeSimulations_TrackerDTCPerformance_Hash_hh

#include <functional>
#include "DataFormats/DetId/interface/DetId.h"

namespace TrackerDTCPerformance
{
	// hash_combine as in BOOST Libraries
	inline void hash_combine(std::size_t& seed) { }
	
	template <typename T, typename... Rest>
	inline void hash_combine(std::size_t& seed, const T& v, Rest... rest)
	{
			std::hash<T> hasher;
			seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
			hash_combine(seed, rest...);
	}
	
	
	template <typename T, typename... Rest>
	inline std::size_t hash_many(const T& v, Rest... rest)
	{
		constexpr std::size_t const seed = 0;
		return hash_combine(seed, v, rest...);
	}
}

namespace std
{
	template <>
	struct hash<DetId>
	{
		size_t operator()(const DetId& k) const
		{
			return k.rawId();
		}
	};
}


#endif // end SLHCUpgradeSimulations_TrackerDTCPerformance_Hash_hh
