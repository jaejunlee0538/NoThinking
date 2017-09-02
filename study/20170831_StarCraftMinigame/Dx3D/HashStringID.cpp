#include "stdafx.h"
#include "HashStringID.h"
namespace qwer {
	struct NameTableEntry {
		int nRefCount;
		size_t nLength;
		size_t nAllocSize;

		const char* GetStr() { return (char*)(this + 1); }
		void AddRef() { nRefCount++; }
		int Release() { return --nRefCount; }
		size_t GetMemoryUsage() { return sizeof(NameTableEntry) + strlen(GetStr()); }
		size_t GetLength() { return nLength; }
	};

	class NameTable {
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
		typedef std::unordered_map<const char*, NameTableEntry*, HashFunc, HashFunc> NameTableType;
		NameTableType m_nameTable;

	public:
		NameTable() {

		}

		~NameTable() {
			for (auto it = m_nameTable.begin(); it != m_nameTable.end(); ++it) {
				free(it->second);
			}
		}

		NameTableEntry* FindName(const char* str) {
			NameTableEntry* pEntry = FindInMap(m_nameTable, str, nullptr);
			return pEntry;
		}

		NameTableEntry* GetName(const char* str) {
			NameTableEntry* pEntry = FindInMap(m_nameTable, str, nullptr);
			if (!pEntry) {
				size_t nStrLen = strlen(str);
				size_t nAllocLen = sizeof(NameTableEntry) + (nStrLen + 1) * sizeof(char);
				pEntry = (NameTableEntry*)malloc(nAllocLen);
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

		void RemoveName(NameTableEntry* pEntry) {
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
	
	NameTable* CName::m_pNameTable = nullptr;

	CName::CName()
		:m_pStr(nullptr){
	}

	CName::CName(const CName& name){
		_AddRef(name.m_pStr);
		m_pStr = name.m_pStr;
	}

	CName::CName(const char * str){
		const char* pStr = nullptr;
		if (pStr && *pStr)
			pStr = GetNameTable()->GetName(str)->GetStr();
		_AddRef(pStr);
		m_pStr = pStr;
	}

	CName::~CName()
	{
		_Release(m_pStr);
	}

	CName & CName::operator=(const CName & name)
	{
		_AddRef(name.m_pStr);
		_Release(m_pStr);
		m_pStr = name.m_pStr;
		return *this;
	}

	CName & CName::operator=(const char * str)
	{
		const char* pStr = nullptr;
		if (str && *str)
			pStr = GetNameTable()->GetName(str)->GetStr();
		_AddRef(pStr);
		_Release(m_pStr);
		m_pStr = pStr;
		return *this;
	}

	bool CName::operator==(const CName & name) const
	{
		return m_pStr == name.m_pStr;
	}

	bool CName::operator<(const CName & name) const
	{
		return m_pStr < name.m_pStr;
	}

	bool CName::Empty() const {
		return m_pStr == nullptr;
	}

	void CName::Reset() {
		_Release(m_pStr);
		m_pStr = nullptr;
	}

	void CName::AddRef() {
		_AddRef(m_pStr);
	}

	const char * CName::c_str() const {
		return m_pStr ? m_pStr : "";
	}

	size_t CName::Length() const {
		return m_pStr ? ((NameTableEntry*)m_pStr)->nLength : 0;
	}

	bool CName::HasName(const char * str) {
		return GetNameTable()->FindName(str) != 0;
	}

	size_t CName::GetNumberOfNames(){
		return GetNameTable()->GetNumberOfNames();
	}

	void CName::ReleaseNameTable()
	{
		SAFE_DELETE(m_pNameTable);
	}

	NameTable * CName::GetNameTable()
	{
		if (m_pNameTable) {
			m_pNameTable = new NameTable();
		}
		return m_pNameTable;
	}

	void CName::_AddRef(const char * pStr)
	{
		if (pStr) {
			((NameTableEntry*)pStr)->AddRef();
		}
	}

	int CName::_Release(const char * pStr)
	{
		if (pStr) {
			NameTableEntry* pNameEntry = ((NameTableEntry*)pStr);
			if (pNameEntry->Release() <= 0) {
				GetNameTable()->RemoveName(pNameEntry);
			}
		}
	}
}