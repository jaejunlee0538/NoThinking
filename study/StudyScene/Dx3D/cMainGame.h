#pragma once

class cMainGame
{
	
private:
	HDC _hdc;

public:
	cMainGame(void);
	virtual ~cMainGame(void);

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();
	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

