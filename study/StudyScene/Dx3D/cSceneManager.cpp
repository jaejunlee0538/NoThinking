#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameScene.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�ؾ� �� setup �Լ� ����
	cSceneManager::m_ReadyScene->Setup();

	//������� ��ü�� ������!!
	cSceneManager::m_pCurrentScene = cSceneManager::m_ReadyScene;

	//����...
	cSceneManager::m_pLoadingScene->~cGameScene();
	cSceneManager::m_pLoadingScene = NULL;
	cSceneManager::m_ReadyScene = NULL;

	return NULL;
}

cGameScene* cSceneManager::m_pCurrentScene = NULL;
cGameScene* cSceneManager::m_pLoadingScene = NULL;
cGameScene* cSceneManager::m_ReadyScene = NULL;

cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

void cSceneManager::Setup(void)
{
	m_pCurrentScene = NULL;
	m_pLoadingScene = NULL;
	m_ReadyScene = NULL;

}

void cSceneManager::release(void)
{
	//���� ��� ���鼭 ����..
	mapSceneIter iter = m_mapSceneList.begin();

	for (; iter != m_mapSceneList.end();)
	{
		//���� �� ������ �ݺ��� ���� x
		if (iter->second != NULL)
		{
			if (m_pCurrentScene == iter->second) iter->second->~cGameScene();
			SAFE_DELETE(iter->second);
			iter = m_mapSceneList.erase(iter);
		}
		else //�ݺ��� ����!
		{
			++iter;
		}
	}

	m_pCurrentScene = NULL;
	m_mapSceneList.clear();
}

void cSceneManager::update(void)
{
	if (m_pCurrentScene) m_pCurrentScene->Update();
}

void cSceneManager::render(void)
{
	if (m_pCurrentScene) m_pCurrentScene->Render();
}

cGameScene * cSceneManager::addScene(string sceneName, cGameScene * scene)
{
	if (!scene) return NULL;
	m_mapSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

HRESULT cSceneManager::changeScene(string sceneName)
{
	//��ü�ؾ� �� ���� ã�´�
	mapSceneIter find = m_mapSceneList.find(sceneName);

	//��ü ���� ������ �޽�..
	if (find == m_mapSceneList.end()) return E_FAIL;

	//��ü �� �ʱ�ȭ
	if (SUCCEEDED(find->second->Setup()))
	{
		if (m_pCurrentScene)
			delete m_pCurrentScene;
		m_pCurrentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

