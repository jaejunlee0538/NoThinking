#pragma once
#include "CRC32.h"
#include <unordered_map>
#include "STLUtils.h"
namespace qwer {
	class NameTable;

	class CName {
	public:
		CName();
		CName(const CName& name);
		explicit CName(const char* str);
		~CName();

		CName& operator=(const CName& name);
		CName& operator=(const char* str);

		bool operator==(const CName& name) const;
		bool operator<(const CName& name) const;

		bool Empty() const;
		void Reset();
		void AddRef();
		const char* c_str() const;
		size_t Length() const;

		static bool HasName(const char* str);
		static size_t GetNumberOfNames();
		static void ReleaseNameTable();
	private:
		static NameTable* GetNameTable();
		static void _AddRef(const char* pStr);
		static int _Release(const char* pStr);
		static NameTable* m_pNameTable;
		
		const char* m_pStr;
	};

	class HashStringId
	{
	public:
		HashStringId()
		:m_nId(0) {
		}

		explicit HashStringId(const char* str) {
			ComputeCRC(str);
		}

		HashStringId(const HashStringId& hs) {
			m_nId = hs.m_nId;
		}

		~HashStringId(){
			
		}
		
		uint32_t Get() const{
			return m_nId;
		}

		HashStringId& operator=(const HashStringId& hs)
		{
			m_nId = hs.m_nId;
			return *this;
		}

		bool operator==(const HashStringId& hs) const
		{
			return m_nId == hs.m_nId;
		}

		bool operator!=(const HashStringId& hs) const
		{
			return m_nId != hs.m_nId;
		}

		bool operator==(const char* str) const
		{
			assert(str);
			if (*str){
				return m_nId == CRC32::Compute(str);
			}
			return m_nId == 0;
		}

		bool operator!=(const char* str) const
		{
			assert(str);
			if (m_nId == 0)
				return true;

			if(*str){
				return m_nId == CRC32::Compute(str);
			}
			return false;
		}

		bool operator<(const HashStringId& hs) const
		{
			return m_nId < hs.m_nId;
		}

		bool operator>(const HashStringId& hs) const
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

	inline bool operator==(const std::string& str, const HashStringId& hs)
	{
		return hs == HashStringId(str.c_str());
	}

	inline bool operator!=(const std::string& str, const HashStringId& hs)
	{
		return hs != HashStringId(str.c_str());
	}

	inline bool operator==(const char* str, const HashStringId& hs)
	{
		return hs == HashStringId(str);
	}

	inline bool operator!=(const char* str, const HashStringId& hs)
	{
		return hs != HashStringId(str);
	}
}
