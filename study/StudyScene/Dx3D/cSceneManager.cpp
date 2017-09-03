#include "stdafx.h"
#include "cSceneManager.h"
#include "cMainGame.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�ؾ� �� setup �Լ� ����
	cSceneManager::_readyScene->Setup();

	//������� ��ü�� ������!!
	cSceneManager::_currentScene = cSceneManager::_readyScene;

	//����...
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

