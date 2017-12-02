#include "stdafx.h"
#include "GraphicSystem.h"
#include <effect11\d3dx11effect.h>
#include <NT_Logging\Logger.h>
#include <NT_Common\MacroUtils.h>
#include <NT_Common\TimeManager.h>
namespace qwer {
	GraphicSystem::GraphicSystem()
		:m_HWND(0), m_D3DDevice(nullptr), m_FPSMeasurer(1.0f)
	{
	}

	GraphicSystem::~GraphicSystem()
	{
	}

	bool GraphicSystem::StartUp(BOOL windowed, HWND hWnd)
	{
		
		return true;
	}

	void GraphicSystem::ShutDown()
	{
		
	}

	void GraphicSystem::Render()
	{
		m_FPSMeasurer.update(GET_TIMEMANAGER().CurrentRealTime());

	}
	void GraphicSystem::EnableDrawFPS(bool enable) {
		m_enableDrawFPS = enable;
	}
	bool GraphicSystem::IsDrawFPSEnabled() const {
		return m_enableDrawFPS;
	}
	HWND GraphicSystem::GetHWND() {
		return m_HWND;
	}
	GraphicDeviceBase* GraphicSystem::GetDeivce() {
		return m_graphicDevice;
	}
}