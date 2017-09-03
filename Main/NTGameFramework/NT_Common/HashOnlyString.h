#pragma once
#include <NT_Common\CRC32.h>
#include <assert.h>

namespace qwer
{
	class HashOnlyString
	{
	public:
		HashOnlyString()
			:m_nId(0) {
		}

		explicit HashOnlyString(const char* str) {
			ComputeCRC(str);
		}

		HashOnlyString(const HashOnlyString& hs) {
			m_nId = hs.m_nId;
		}

		~HashOnlyString() {

		}

		uint32_t Get() const {
			return m_nId;
		}

		HashOnlyString& operator=(const HashOnlyString& hs)
		{
			m_nId = hs.m_nId;
			return *this;
		}

		bool operator==(const HashOnlyString& hs) const
		{
			return m_nId == hs.m_nId;
		}

		bool operator!=(const HashOnlyString& hs) const
		{
			return m_nId != hs.m_nId;
		}

		bool operator==(const char* str) const
		{
			assert(str);
			if (*str) {
				return m_nId == CRC32::Compute(str);
			}
			return m_nId == 0;
		}

		bool operator!=(const char* str) const
		{
			assert(str);
			if (m_nId == 0)
				return true;

			if (*str) {
				return m_nId == CRC32::Compute(str);
			}
			return false;
		}

		bool operator<(const HashOnlyString& hs) const
		{
			return m_nId < hs.m_nId;
		}

		bool operator>(const HashOnlyString& hs) const
		{
			return m_nId > hs.m_nId;
		}
	private:
		void ComputeCRC(const char* str)
		{
			m_nId = CRC32::Compute(str);
		}

		uint32_t m_nId;
	};

	inline bool operator==(const std::string& str, const HashOnlyString& hs)
	{
		return hs == HashOnlyString(str.c_str());
	}

	inline bool operator!=(const std::string& str, const HashOnlyString& hs)
	{
		return hs != HashOnlyString(str.c_str());
	}

	inline bool operator==(const char* str, const HashOnlyString& hs)
	{
		return hs == HashOnlyString(str);
	}

	inline bool operator!=(const char* str, const HashOnlyString& hs)
	{
		return hs != HashOnlyString(str);
	}
}