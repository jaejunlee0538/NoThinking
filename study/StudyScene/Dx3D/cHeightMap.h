#pragma once
#include "cUIButton.h"
#include "cMainGame.h"

class cGrid;
class cCamera;
class cCrtCtrl;
class iMap;
class cSkinnedMesh;
class cFrustum;
class cTerrain;

class cHeightMap : public cMainGame
{
private:
	cGrid*			m_pGrid;
	cCamera*		m_pCamera;
	cCrtCtrl*		m_pCrtCtrl;
	LPD3DXFONT		m_pFont;
	iMap*			m_pMap;
	cFrustum*		m_pFrustum;
	LPD3DXSPRITE	m_pSprite;
	cUIObject*		m_pUIRoot;
	cGameObject*	m_RootObject;

	vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXIMAGE_INFO		m_stImageInfo;


	//==================0824
	vector<float>		m_vecHeight;
	cTerrain*			m_pTerrain;

public:
	cHeightMap(void);
	~cHeightMap(void);

	HRESULT Setup();
	void Update();
	void Render();
	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();


};

