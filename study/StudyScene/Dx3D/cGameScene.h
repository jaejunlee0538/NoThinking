#pragma once

#include "cMainGame.h"

#include "cHeightMap.h"

class cGameScene :public cMainGame
{
public:
	cGameScene();
	~cGameScene();

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();
	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

