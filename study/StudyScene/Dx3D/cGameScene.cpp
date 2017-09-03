#include "stdafx.h"
#include "cGameScene.h"


cGameScene::cGameScene()
{
}


cGameScene::~cGameScene()
{
}

HRESULT cGameScene::Setup()
{
	cMainGame::Setup();

	g_pSceneManager->addScene("cHeightMap", new cHeightMap);

	g_pSceneManager->changeScene("cHeightMap");

	return S_OK;
}

void cGameScene::Update()
{
	cMainGame::Update();

	g_pSceneManager->update();

}

void cGameScene::Render()
{
	cMainGame::Render();

	g_pSceneManager->render();

}

void cGameScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
