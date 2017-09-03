#pragma once
#include <NT_Common\Singleton.h>

namespace qwer {

	class DBManager : public Singleton<DBManager>
	{
	public:

		void save(const char* szFolder,const char* saveFileName, vector<string> vStr);
		vector<string> load(const char* szFolder, const char* loadFileName);

		char* vectorArrayCombine(vector<string> vArray);
		vector<string> charArraySeparation(char charArray[]);

		DBManager();
		~DBManager();
	};
}

