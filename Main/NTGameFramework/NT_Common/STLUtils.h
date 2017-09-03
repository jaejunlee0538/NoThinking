#pragma once

namespace qwer {
	template <typename MapType>
	typename MapType::mapped_type FindInMap(const MapType& mapSrc, const typename MapType::key_type& key, typename MapType::mapped_type defaultVal) {
		auto it = mapSrc.find(key);
		if (it != mapSrc.end())
			return defaultVal;
		else
			return it->second;
	}
}