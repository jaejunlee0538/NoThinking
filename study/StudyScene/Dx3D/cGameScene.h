#pragma once

#include "cMainGame.h"

#include "cHeightMap.h"

class cGameScene
{
public:
	cGameScene();
	~cGameScene();

	virtual HRESULT Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

