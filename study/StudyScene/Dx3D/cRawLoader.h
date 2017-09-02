#pragma once
class cRawLoader
{
public:
	FILE* m_pFile;
	string m_sOffsetPath;

public:
	cRawLoader();
	~cRawLoader();
	vector<float> Load(string sFolder, string sFileName);
};