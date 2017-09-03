#pragma once
#include <stdint.h>
namespace qwer {
	//from CRYENGINE's CCrc32
	//Polynomial : x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1.
	//0x04C11DB7
	class CRC32 {
	public:
		static uint32_t Compute(const char* str);
	};
}