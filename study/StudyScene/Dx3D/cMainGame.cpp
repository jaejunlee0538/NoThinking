#include "StdAfx.h"
#include "cMainGame.h"
#include "cSceneManager.h"
#include "LoadingScene.h"
cMainGame::cMainGame(void)
{
}

cMainGame::~cMainGame(void)
{

}

HRESULT cMainGame::Setup()
{
	g_pD3DDevice;

	g_pSceneManager->addScene("LoadingScene", new LoadingScene());
	g_pSceneManager->changeScene("LoadingScene");
	return S_OK;
}

void cMainGame::Update()
{
	g_pSceneManager->update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(
		0, 0, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	g_pSceneManager->render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(0, 0, 0, 0);
}

void cMainGame::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//MsgProc
}
