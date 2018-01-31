#ifndef DataFormats_DetId_DetIdHash_h
#define DataFormats_DetId_DetIdHash_h

#include "DataFormats/DetId/interface/DetId.h"

// Specialization of std::hash for DetId, so DetId can be used in unordered containers

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

#endif // DataFormats_DetId_DetIdHash_h
