#include "stdafx.h"
#include "WindowSystem.h"
#include <Windows.h>
#include "TimeManager.h"
#include "FreqEstimater.h"

namespace qwer {
	namespace {
		WindowSystem* app = nullptr;
	}
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return app->MsgProc(hWnd, message, wParam, lParam);
	}

	WindowSystem::WindowSystem(HINSTANCE hInstance)
		:m_hInstance(hInstance)
	{
		app = this;
	}

	WindowSystem::~WindowSystem()
	{
	}

	bool WindowSystem::StartUp()
	{
		if (InitWindow() == false)
			return false;
		return true;
	}

	void WindowSystem::Shutdown()
	{
	}

	void WindowSystem::Loop()
	{
		MSG msg;
		FreqEstimater freq(1.0f);
		char buffer[256];
		while (true) {
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					break;
				}
				else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else {
				TimeManager::GetSingleton().Update();
				freq.update(TimeManager::GetSingleton().CurrentRealTime());
				RenderDeviceManager::GetSingleton().GetDevice()->Clear(
					0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
				RenderDeviceManager::GetSingleton().GetDevice()->BeginScene();

				RenderDeviceManager::GetSingleton().GetDevice()->EndScene();
				RenderDeviceManager::GetSingleton().GetDevice()->Present(0, 0, 0, 0);
				//
				sprintf_s(buffer, 256, "FSP:%.1lf Time:%.2lf Real-Time:%.2lf", freq.getFPS(), TimeManager::GetSingleton().CurrentTime(), TimeManager::GetSingleton().CurrentRealTime());
				SetWindowTextA(m_hWnd, buffer);
			}
		}
	}

	HRESULT WindowSystem::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	bool WindowSystem::InitWindow()
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

		HWND hWnd = CreateWindowA("GameApp", "GameApp", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

		if (!hWnd) {
			return false;
		}
		m_hWnd = hWnd;
		RECT rect = { 0, 0, 800, 600 };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(m_hWnd, NULL, 50, 50, rect.right - rect.left,
			rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);

		ShowWindow(hWnd, SW_SHOW);
		return true;
	}
}