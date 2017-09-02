#pragma once
#include "Singleton.h"
namespace qwer {
	class WindowSystem : public Singleton<WindowSystem>
	{
	public:
		WindowSystem(HINSTANCE hInstance);
		~WindowSystem();

		bool StartUp();
		void Shutdown();
		void Loop();

		HRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND GetHWND() {
			return m_hWnd;
		}
	private:
		bool InitWindow();
		int m_windowWidth;
		int m_windowHeight;
		HINSTANCE	m_hInstance;
		HWND		m_hWnd;
	};
}