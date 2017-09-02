// Game3DFramework.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowSystem.h"
#include "Singleton.h"
#include "LogTargetDebugStream.h"
#include "LogTargetFile.h"
#include "GraphicSystem.h"
#include "HashStringID.h"
#include "FreqEstimater.h"

#define MAX_LOADSTRING 100
using namespace qwer;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   
	TimeManager timeManager;
	Logging::Logger logger;
	Logging::LogTargetDebugStream logDebugStream;
	Logging::LogTargetFile	logFile("gameLog.log");
	GraphicSystem graphicSystem;
	WindowSystem window(hInstance);

	timeManager.StartUp();

	logger.StartUp();
	logger.AddLogTarget(&logDebugStream);
	logger.AddLogTarget(&logFile);

	LOG_INFO(Logging::CHANNEL_GENERAL, "Creating GameApp");
	
	if (window.StartUp() == false) {
		LOG_ERROR(Logging::CHANNEL_CORE, "Error while creating GameApp");
		goto Shutdown_From_Logger;
	}

	LOG_INFO(Logging::CHANNEL_CORE, "Creating RenderDeviceManager");

	if (GraphicSystem::GetSingleton().StartUp(TRUE, window.GetHWND()) == false) {
		LOG_ERROR(Logging::CHANNEL_CORE, "Error while creating RenderDeviceManager");
		goto Shutdown_From_Gameapp;
	}

	//게임 루프 시작
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
			GraphicSystem::GetSingleton().REn
		}
	}

	window.Loop();

Shutdown_From_RenderManager:
	graphicSystem.ShutDown();
Shutdown_From_Gameapp:
	window.Shutdown();
Shutdown_From_Logger:
	logger.Shutdown();
	timeManager.Shutdown();

	CName::ReleaseNameTable();

	return 0;
}
