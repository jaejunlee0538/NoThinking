#include "StdAfx.h"
#include "cMainGame.h"


cMainGame::cMainGame(void)
{
}

cMainGame::~cMainGame(void)
{

}

HRESULT cMainGame::Setup()
{
	_hdc = GetDC(g_hWnd);

	return S_OK;
}

void cMainGame::Update()
{
	
}

void cMainGame::Render()
{
}

void cMainGame::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


