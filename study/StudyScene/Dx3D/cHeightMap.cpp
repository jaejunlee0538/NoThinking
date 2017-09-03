#include "StdAfx.h"
#include "cHeightMap.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCrtCtrl.h"
#include "cAseLoader.h"
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshManager.h"
#include "cFrustum.h"
#include "cObjMap.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
#include "cRawLoader.h"
#include "cTerrain.h"


enum
{
	E_CONFIRM_BUTTON = 213,
	E_CANCEL_BUTTON = 214,
	E_TEXT_VIEW,
};

cHeightMap::cHeightMap(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pCrtCtrl(NULL)
	, m_pFont(NULL)
	, m_pMap(NULL)
	, m_pFrustum(NULL)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUIRoot(NULL)
	, m_RootObject(NULL)
	, m_pTerrain(NULL)
{
}

cHeightMap::~cHeightMap(void)
{

	cGameScene::~cGameScene();

	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCrtCtrl);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pFrustum);
	SAFE_DELETE(m_RootObject);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pFont);
	SAFE_DELETE(m_pTerrain);

	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pUIRoot);

	g_pFontManager->Destroy();
	g_pObjectPool->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pDeviceManager->Destroy();
}

HRESULT cHeightMap::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_RootObject = new cGameObject;
	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zealot/", "Zealot.X");
	pSkinnedMesh->m_matRoot = m_RootObject->GetWorldTM();
	m_vecSkinnedMesh.push_back(pSkinnedMesh);

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCrtCtrl = new cCrtCtrl;
	m_pCamera = new cCamera;

	D3DXVECTOR3* crtPos = m_RootObject->getPointpos();
	m_pCamera->Setup(crtPos);

	cRawLoader raw;
	m_vecHeight = raw.Load("", "HeightMap.raw");

	m_pTerrain = new cTerrain;
	m_pTerrain->setRawHeight(m_vecHeight);
	m_pTerrain->Setup();


	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	SetLight();

	return S_OK;
}

void cHeightMap::Update()
{
	g_pTimeManager->Update();

	//if (m_pCrtCtrl) m_pCrtCtrl->Update(m_pMap);
	if (m_pCamera) m_pCamera->Update();
	if (m_RootObject)m_RootObject->Update();
	if (m_pTerrain)m_pTerrain->Update();
	float height;
	height = m_pTerrain->GetHeight(m_RootObject->GetPosition());

	for each (auto p in m_vecSkinnedMesh)
	{
		p->m_matRoot = m_RootObject->GetWorldTM();
		p->m_matRoot._42 = height;
	}
	if (m_RootObject->getMoving()) {
		for each (auto p in m_vecSkinnedMesh)
		{
			p->SetAnimationIndex(3);
			p->m_matRoot._42 = height;
		}
	}
	else if (!m_RootObject->getMoving()) {
		for each (auto p in m_vecSkinnedMesh)
		{
			p->SetAnimationIndex(4);
			p->m_matRoot._42 = height;
		}
	}
	g_pAutoReleasePool->Drain();


}

void cHeightMap::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pTerrain)m_pTerrain->Render();

	for each (auto p in m_vecSkinnedMesh)
	{
		p->UpdateAndRender();
	}


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


void cHeightMap::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->MsgProc(hWnd, message, wParam, lParam);
	}
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_SPACE:
		{
		}
		break;
		}
		break;
	}
}

void cHeightMap::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}
