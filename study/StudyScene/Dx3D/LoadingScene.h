#pragma once
#include "cGameScene.h"

class LoadingScene :
	public cGameScene
{
public:
	LoadingScene();
	~LoadingScene();

	virtual HRESULT Setup() override{
		return S_OK;
	}
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override {}
};

