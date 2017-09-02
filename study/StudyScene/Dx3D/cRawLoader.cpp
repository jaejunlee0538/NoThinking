#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
{
}


cRawLoader::~cRawLoader()
{
}

vector<float> cRawLoader::Load(string sFolder, string sFileName)
{
	vector<float> vecHeight;
	m_sOffsetPath = "HeightMapData/";
	string sFilePath = sFolder + m_sOffsetPath + sFileName;
	fopen_s(&m_pFile, sFilePath.c_str(), "rb");
	while (!feof(m_pFile))
	{
		short ch = fgetc(m_pFile);
		vecHeight.push_back(ch);
	}
	fclose(m_pFile);
	return vecHeight;
}
