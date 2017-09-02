#pragma once
#include <bitset>


#define KEYMAX 256
#define g_pKeyManager cKeyManager::GetInstance()

class cKeyManager
{

private:
	SINGLETON(cKeyManager)

private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT init(void);
	void release(void);

	//�ѹ��� ��������..
	bool isOnceKeyDown(int key);

	//�ѹ��� ��������..
	bool isOnceKeyUp(int key);

	//��� ������ ������..
	bool isStayKeyDown(int key);

	//���� on ���� off ~~~~~ (���� ����ġ ����...)
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

};

