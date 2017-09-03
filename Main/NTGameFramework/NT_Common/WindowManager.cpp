#include "stdafx.h"
#include "WindowManager.h"
#include <NT_Common/TimeManager.h>
#include <NT_Common/FreqEstimater.h>
#include <NT_Common/DBManager.h>
#include <NT_Input/InputManager.h>

namespace qwer {
	namespace {
		WindowManager* app = nullptr;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return app->MsgProc(hWnd, message, wParam, lParam);
	}

	WindowManager::WindowManager(HINSTANCE hInstance)
		:m_hInstance(hInstance)
	{
		app = this;
	}

	WindowManager::~WindowManager()
	{
	}

	bool WindowManager::StartUp(int width, int height)
	{
		if (InitWindow(width, height) == false)
			return false;
		return true;
	}

	void WindowManager::Shutdown()
	{
	}

	HRESULT WindowManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
			return true;
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	bool WindowManager::InitWindow(int width, int height)
	{
		WNDCLASS wndClass;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hInstance = m_hInstance;
		wndClass.lpfnWndProc = (WNDPROC)WndProc;
		wndClass.lpszClassName = "GameApp";
		wndClass.lpszMenuName = NULL;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&wndClass);
		//WS_OVERLAPPEDWINDOW은 WS_THICKFRAME을 포함하고 있어서 윈도우창 크기를 조절할 수 있다.
		//윈도우 창 크기 조절을 막기 위해 WS_THICKFRAME이 제거되도록 style을 설정한다.
		int winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		HWND hWnd = CreateWindowA("GameApp", "GameApp", winStyle,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

		if (!hWnd) {
			return false;
		}
		m_hWnd = hWnd;
		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, winStyle, false);
		SetWindowPos(m_hWnd, NULL, 50, 50, rect.right - rect.left,
			rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);

		ShowWindow(hWnd, SW_SHOW);
		return true;
	}
}