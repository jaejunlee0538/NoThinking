#include "stdafx.h"
#include <NT_Common\WindowManager.h>
#include <NT_Common\TimeManager.h>
#include <NT_Logging\Logger.h>
#include <NT_Logging\LogTargetDebugStream.h>
#include <NT_Logging\LogTargetFile.h>
#include <NT_Graphic\GraphicSystem.h>
#include <NT_Common\HashedString.h>
#include <NT_Common\FreqEstimater.h>
#include <NT_Input\InputManager.h>
#include <NT_Sound\SoundManager.h>

#define STARTUP_MANAGER(Mgr, ...) \
LOG_INFO(Logging::CHANNEL_CORE, #Mgr" 초기화");\
if(!Mgr.StartUp(__VA_ARGS__)){\
	LOG_ERROR(Logging::CHANNEL_CORE, #Mgr" 초기화 에러");\
	goto Shutdown_Systems;\
}
#define MAX_LOADSTRING 100

using namespace qwer;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//TimeManager/Logger 클래스 초기화
	TimeManager timeManager;
	Logging::Logger logger;
	Logging::LogTargetDebugStream logDebugStream;
	Logging::LogTargetFile	logFile("gameLog.log");

	timeManager.StartUp();
	logger.StartUp();
	logger.AddLogTarget(&logDebugStream);
	logger.AddLogTarget(&logFile);

	//System과 Manager 클래스 초기화
	GraphicSystem graphicSystem;
	WindowManager windowManager(hInstance);
	InputManager inputManager;
	SoundManager soundManager;

	STARTUP_MANAGER(windowManager, 800, 600);
	STARTUP_MANAGER(graphicSystem, TRUE, windowManager.GetHWND());
	STARTUP_MANAGER(inputManager);
	STARTUP_MANAGER(soundManager);
	{
		//게임 루프 시작
		MSG msg;
		FreqEstimater freq(1.0f);
		char buffer[256];
		HWND hWnd = windowManager.GetHWND();
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
				timeManager.Update();
				freq.update(timeManager.CurrentRealTime());
				graphicSystem.Render();

				//윈도우 타이틀바에 FPS출력
				sprintf_s(buffer, 256,
					"FPS : %.1lf Time:%.2lf Real-Time:%.2lf",
					freq.getFPS(),
					timeManager.CurrentTime(),
					timeManager.CurrentRealTime());
				SetWindowTextA(hWnd, buffer);
			}
		}
	}

Shutdown_Systems:
	soundManager.Shutdown();
	inputManager.Shutdown();
	graphicSystem.ShutDown();
	windowManager.Shutdown();
	logger.Shutdown();
	timeManager.Shutdown();

	HashedString::ReleaseNameTable();

	return 0;
}
