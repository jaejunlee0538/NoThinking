#pragma once
#include <NT_Common\Singleton.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>

namespace qwer {

	class DBManager : public Singleton<DBManager>
	{
	public:
		DBManager();
		~DBManager();

		void save(const char* szFolder, const char* saveFileName, std::vector<std::string> vStr);
		std::vector<std::string> load(const char* szFolder, const char* loadFileName);

		char* vectorArrayCombine(std::vector<std::string> vArray);
		std::vector<std::string> charArraySeparation(char charArray[]);

	};
}
#define GET_DBMANAGER() qwer::DBManager::GetSingleton()