#pragma once

class cMainGame
{
public:
	cMainGame(void);
	virtual ~cMainGame(void);

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

