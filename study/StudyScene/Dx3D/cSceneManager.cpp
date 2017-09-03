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

void cSceneManager::Setup(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

}

void cSceneManager::release(void)
{
	//���� ��� ���鼭 ����..
	mapSceneIter iter = _mSceneList.begin();

	for (; iter != _mSceneList.end();)
	{
		//���� �� ������ �ݺ��� ���� x
		if (iter->second != NULL)
		{
			if (_currentScene == iter->second) iter->second->~cMainGame();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else //�ݺ��� ����!
		{
			++iter;
		}
	}

	_currentScene = NULL;
	_mSceneList.clear();
}

void cSceneManager::update(void)
{
	if (_currentScene) _currentScene->Update();
}

void cSceneManager::render(void)
{
	if (_currentScene) _currentScene->Render();
}

cMainGame * cSceneManager::addScene(string sceneName, cMainGame * scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

bool cSceneManager::changeScene(string sceneName)
{
	//��ü�ؾ� �� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//��ü ���� ������ �޽�..
	if (find == _mSceneList.end()) return false;

	//��ü �� �ʱ�ȭ
	if (_currentScene) 
	{
		_currentScene->~cMainGame();
		_currentScene = find->second;

		return true;
	}

	return false;
}

