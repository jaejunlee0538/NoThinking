#pragma once
#include <NT_Common\Singleton.h>
#include <Windows.h>
namespace qwer {
	class WindowManager : public Singleton<WindowManager>
	{
	public:
		WindowManager(HINSTANCE hInstance);
		~WindowManager();

		bool StartUp(int width, int height);
		void Shutdown();

		HRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND GetHWND() {
			return m_HWND;
		}
	private:
		bool InitWindow(int width, int height);
		int m_windowWidth;
		int m_windowHeight;
		HINSTANCE	m_hInstance;
		HWND		m_HWND;
	};
}