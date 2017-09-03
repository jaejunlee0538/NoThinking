#pragma once

namespace qwer {
	class StringTable;

	class HashedString {
	public:
		HashedString();
		HashedString(const HashedString& name);
		explicit HashedString(const char* str);
		~HashedString();

		HashedString& operator=(const HashedString& name);
		HashedString& operator=(const char* str);

		bool operator==(const HashedString& name) const;
		bool operator<(const HashedString& name) const;

		bool Empty() const;
		void Reset();
		const char* c_str() const;
		size_t Length() const;

		static bool HasName(const char* str);
		static size_t GetNumberOfNames();
		static void ReleaseNameTable();
	private:
		//������ RefCounting�� ���� �ּ� ��ȯ �����ڸ� ����� �����ϳ�.
		void* operator&() { return this; }
		static StringTable* GetNameTable();
		static void _AddRef(const char* pStr);
		static void _Release(const char* pStr);
		static StringTable* m_pNameTable;
		
		const char* m_pStr;
	};
}
