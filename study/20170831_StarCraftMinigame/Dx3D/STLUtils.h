#pragma once

namespace qwer {
	template <typename MapType>
	T FindInMap(const MapType& mapSrc, const typename MapType::key_type& key, typename MapType::mapped_type defaultVal) {
		auto it = mapSrc.fine(key);
		if (it != mapSrc.end())
			return defaultVal;
		else
			return it->second;
	}
}