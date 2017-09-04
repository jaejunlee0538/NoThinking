#include "stdafx.h"
#include "DBManager.h"

namespace qwer {
	DBManager::DBManager()
	{
	}


	DBManager::~DBManager()
	{
	}

	void DBManager::save(const char* szFolder, const char* saveFileName, std::vector<std::string> vStr)
	{
		HANDLE file;
		char str[128];
		DWORD write;

		strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

		file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, str, strlen(str), &write, NULL);
		CloseHandle(file);
	}
	std::vector<std::string> DBManager::load(const char* szFolder, const char* loadFileName)
	{
		HANDLE file;
		char str[128];
		DWORD read;

		memset(str, 0, 128);
		file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, str, 128, &read, NULL);
		CloseHandle(file);

		return charArraySeparation(str);
	}

	char* DBManager::vectorArrayCombine(std::vector<std::string> vArray)
	{
		char str[128];

		ZeroMemory(str, sizeof(str));

		for (int i = 0; i < vArray.size(); i++)
		{
			strncat_s(str, 128, vArray[i].c_str(), 126);
			if (i + 1 < vArray.size()) strcat_s(str, ",");
		}

		return str;
	}
	std::vector<std::string> DBManager::charArraySeparation(char charArray[])
	{
		std::vector<std::string> vArray;
		char* separation = ",+=*&^%$#@";
		char* token;
		char** content = NULL;

		token = strtok_s(charArray, separation, content);
		vArray.push_back(token);

		while (NULL != (token = strtok_s(NULL, separation, content)))
		{
			vArray.push_back(token);
		}
		return vArray;
	}

}