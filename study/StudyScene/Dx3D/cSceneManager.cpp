#include "stdafx.h"
#include "cSceneManager.h"
#include "cMainGame.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체해야 할 setup 함수 실행
	cSceneManager::_readyScene->Setup();

	//현재씬을 교체될 씬으로!!
	cSceneManager::_currentScene = cSceneManager::_readyScene;

	//해제...
	cSceneManager::_loadingScene->~cMainGame();
	cSceneManager::_loadingScene = NULL;
	cSceneManager::_readyScene = NULL;

	return NULL;
}

cMainGame* cSceneManager::_currentScene = NULL;
cMainGame* cSceneManager::_loadingScene = NULL;
cMainGame* cSceneManager::_readyScene = NULL;

cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

HRESULT cSceneManager::Setup(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void cSceneManager::release(void)
{
}

void cSceneManager::update(void)
{
}

void cSceneManager::render(void)
{
}

cMainGame * cSceneManager::addScene(string sceneName, cMainGame * scene)
{
	return nullptr;
}

HRESULT cSceneManager::changeScene(string sceneName)
{
	return E_NOTIMPL;
}

