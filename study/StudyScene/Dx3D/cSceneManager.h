#pragma once


#define g_pSceneManager cSceneManager::GetInstance()

class cMainGame;

class cSceneManager
{
private:
	SINGLETON(cSceneManager)

public:
	typedef map<string, cMainGame*> mapSceneList;
	typedef map<string, cMainGame*>::iterator mapSceneIter;

private:
	static cMainGame* _currentScene; //현재씬
	static cMainGame* _loadingScene; //로딩씬
	static cMainGame* _readyScene; //교체 대기 중인 씬

	mapSceneList _mSceneList; //씬리스트

	DWORD _loadThreadID;

public:
	void Setup(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가한다
	cMainGame* addScene(string sceneName, cMainGame* scene);

	//씬 교체...
	HRESULT changeScene(string sceneName);

	//로딩 쓰레드 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);


};

