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
	static cMainGame* _currentScene; //�����
	static cMainGame* _loadingScene; //�ε���
	static cMainGame* _readyScene; //��ü ��� ���� ��

	mapSceneList _mSceneList; //������Ʈ

	DWORD _loadThreadID;

public:
	void Setup(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰��Ѵ�
	cMainGame* addScene(string sceneName, cMainGame* scene);

	//�� ��ü...
	HRESULT changeScene(string sceneName);

	//�ε� ������ �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);


};

