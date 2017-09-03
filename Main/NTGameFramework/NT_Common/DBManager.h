#pragma once
#include <NT_Common\Singleton.h>
#include <vector>
#include <string>

namespace qwer {

	class DBManager : public Singleton<DBManager>
	{
	public:

		void save(const char* szFolder,const char* saveFileName, std::vector<std::string> vStr);
		std::vector<std::string> load(const char* szFolder, const char* loadFileName);

		char* vectorArrayCombine(std::vector<std::string> vArray);
		std::vector<std::string> charArraySeparation(char charArray[]);

		DBManager();
		~DBManager();
	};
}
#define GET_DBMANAGER() qwer::DBManager::GetSingleton()

