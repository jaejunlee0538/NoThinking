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
	static cGameScene* m_pCurrentScene; //�����
	static cGameScene* m_pLoadingScene; //�ε���
	static cGameScene* m_ReadyScene; //��ü ��� ���� ��

	mapSceneList m_mapSceneList; //������Ʈ

	DWORD m_dwLoadThreadID;

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

