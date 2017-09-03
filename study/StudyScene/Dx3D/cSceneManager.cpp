#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameScene.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체해야 할 setup 함수 실행
	cSceneManager::m_ReadyScene->Setup();

	//현재씬을 교체될 씬으로!!
	cSceneManager::m_pCurrentScene = cSceneManager::m_ReadyScene;

	//해제...
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
	//맵을 모두 돌면서 삭제..
	mapSceneIter iter = m_mapSceneList.begin();

	for (; iter != m_mapSceneList.end();)
	{
		//지울 수 있으면 반복자 증가 x
		if (iter->second != NULL)
		{
			if (m_pCurrentScene == iter->second) iter->second->~cGameScene();
			SAFE_DELETE(iter->second);
			iter = m_mapSceneList.erase(iter);
		}
		else //반복자 증가!
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
	//교체해야 할 씬을 찾는다
	mapSceneIter find = m_mapSceneList.find(sceneName);

	//교체 씬이 없으면 펄스..
	if (find == m_mapSceneList.end()) return E_FAIL;

	//교체 씬 초기화
	if (SUCCEEDED(find->second->Setup()))
	{
		if (m_pCurrentScene)
			delete m_pCurrentScene;
		m_pCurrentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

