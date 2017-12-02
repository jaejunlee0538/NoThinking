#pragma once
#include <NT_Common/Singleton.h>
#include <NT_Common/FreqEstimater.h>
#include <NT_Common/MacroUtils.h>
#include "GraphicDeviceBase.h"
namespace qwer {
	
	class GraphicSystem : public Singleton<GraphicSystem>
	{
	private:
		bool				m_enableDrawFPS;
		FreqEstimater		m_FPSMeasurer;

		HWND				m_HWND;
		GraphicDeviceBase*			m_graphicDevice;
	public:
		GraphicSystem();
		~GraphicSystem();

		bool StartUp(BOOL windowed, HWND hWnd);
		void ShutDown();

		void Render();

		void EnableDrawFPS(bool enable);
		bool IsDrawFPSEnabled() const;

		HWND GetHWND();
		GraphicDeviceBase* GetDeivce();
	};
}