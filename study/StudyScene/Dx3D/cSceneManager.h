#pragma once


#define g_pSceneManager cSceneManager::GetInstance()
class cGameScene;
class cSceneManager
{
private:
	SINGLETON(cSceneManager)

public:
	typedef map<string, cGameScene*> mapSceneList;
	typedef map<string, cGameScene*>::iterator mapSceneIter;

private:
	static cGameScene* _currentScene; //�����
	static cGameScene* _loadingScene; //�ε���
	static cGameScene* _readyScene; //��ü ��� ���� ��

	mapSceneList _mSceneList; //������Ʈ

	DWORD _loadThreadID;

public:
	void Setup(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰��Ѵ�
	cGameScene* addScene(string sceneName, cGameScene* scene);

	//�� ��ü...
	HRESULT changeScene(string sceneName);

	//�ε� ������ �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);


};

