#include "stdafx.h"
#include "HashedString.h"
namespace qwer {
	struct StringTableEntry {
		int nRefCount;
		size_t nLength;
		size_t nAllocSize;

		const char* GetStr() { return (char*)(this + 1); }
		void AddRef() { nRefCount++; }
		int Release() { return --nRefCount; }
		size_t GetMemoryUsage() { return sizeof(StringTableEntry) + strlen(GetStr()); }
		size_t GetLength() { return nLength; }
	};

	class StringTable {
	private:
		struct HashFunc
		{
			size_t operator()(const char* str) const
			{
				unsigned int hash = 0;
				while (*str) {
					hash = 5 * hash + tolower(*str);
					++str;
				}
				return size_t(hash);
			}

			bool operator()(const char* str1, const char* str2) const
			{
				return stricmp(str1, str2) == 0;
			}
		};
	private:
		typedef std::unordered_map<const char*, StringTableEntry*, HashFunc, HashFunc> NameTableType;
		NameTableType m_nameTable;

	public:
		StringTable() {

		}

		~StringTable() {
			for (auto it = m_nameTable.begin(); it != m_nameTable.end(); ++it) {
				free(it->second);
			}
		}

		StringTableEntry* FindName(const char* str) {
			StringTableEntry* pEntry = FindInMap(m_nameTable, str, nullptr);
			return pEntry;
		}

		StringTableEntry* GetName(const char* str) {
			StringTableEntry* pEntry = FindInMap(m_nameTable, str, nullptr);
			if (!pEntry) {
				size_t nStrLen = strlen(str);
				size_t nAllocLen = sizeof(StringTableEntry) + (nStrLen + 1) * sizeof(char);
				pEntry = (StringTableEntry*)malloc(nAllocLen);
				assert(pEntry);
				pEntry->nRefCount = 0;
				pEntry->nLength = nStrLen;
				pEntry->nAllocSize = nAllocLen;

				char* pEntryStr = const_cast<char*>(pEntry->GetStr());
				memcpy(pEntryStr, str, nStrLen + 1);

				m_nameTable[pEntry->GetStr()] = pEntry;
			}
			return pEntry;
		}

		void RemoveName(StringTableEntry* pEntry) {
			assert(pEntry);
			if (m_nameTable.erase(pEntry->GetStr())) {
				free(pEntry);
			}
		}

		bool HasName(const char* str) const {
			return FindInMap(m_nameTable, str, nullptr) != nullptr;
		}

		size_t GetNumberOfNames() const {
			return m_nameTable.size();
		}
	};
	
	StringTable* HashedString::m_pNameTable = nullptr;

	HashedString::HashedString()
		:m_pStr(nullptr){
	}

	HashedString::HashedString(const HashedString& name){
		_AddRef(name.m_pStr);
		m_pStr = name.m_pStr;
	}

	HashedString::HashedString(const char * str){
		const char* pStr = nullptr;
		if (pStr && *pStr)
			pStr = GetNameTable()->GetName(str)->GetStr();
		_AddRef(pStr);
		m_pStr = pStr;
	}

	HashedString::~HashedString()
	{
		_Release(m_pStr);
	}

	HashedString & HashedString::operator=(const HashedString & name)
	{
		_AddRef(name.m_pStr);
		_Release(m_pStr);
		m_pStr = name.m_pStr;
		return *this;
	}

	HashedString & HashedString::operator=(const char * str)
	{
		const char* pStr = nullptr;
		if (str && *str)
			pStr = GetNameTable()->GetName(str)->GetStr();
		_AddRef(pStr);
		_Release(m_pStr);
		m_pStr = pStr;
		return *this;
	}

	bool HashedString::operator==(const HashedString & name) const
	{
		return m_pStr == name.m_pStr;
	}

	bool HashedString::operator<(const HashedString & name) const
	{
		return m_pStr < name.m_pStr;
	}

	bool HashedString::Empty() const {
		return m_pStr == nullptr;
	}

	void HashedString::Reset() {
		_Release(m_pStr);
		m_pStr = nullptr;
	}

	void HashedString::AddRef() {
		_AddRef(m_pStr);
	}

	const char * HashedString::c_str() const {
		return m_pStr ? m_pStr : "";
	}

	size_t HashedString::Length() const {
		return m_pStr ? ((StringTableEntry*)m_pStr)->nLength : 0;
	}

	bool HashedString::HasName(const char * str) {
		return GetNameTable()->FindName(str) != 0;
	}

	size_t HashedString::GetNumberOfNames(){
		return GetNameTable()->GetNumberOfNames();
	}

	void HashedString::ReleaseNameTable()
	{
		SAFE_DELETE(m_pNameTable);
	}

	StringTable * HashedString::GetNameTable()
	{
		if (m_pNameTable) {
			m_pNameTable = new StringTable();
		}
		return m_pNameTable;
	}

	void HashedString::_AddRef(const char * pStr)
	{
		if (pStr) {
			((StringTableEntry*)pStr)->AddRef();
		}
	}

	int HashedString::_Release(const char * pStr)
	{
		if (pStr) {
			StringTableEntry* pNameEntry = ((StringTableEntry*)pStr);
			if (pNameEntry->Release() <= 0) {
				GetNameTable()->RemoveName(pNameEntry);
			}
		}
	}
}