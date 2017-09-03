#pragma once
#include <d3dx9.h>
#include <NT_Common/Singleton.h>
#include <NT_Common/FreqEstimater.h>
#include <NT_Common/MacroUtils.h>
namespace qwer {
	typedef LPDIRECT3DDEVICE9 DirectXDevicePtr;

	class GraphicSystem : public Singleton<GraphicSystem>
	{
	private:
		bool				m_bDrawFPS;
		FreqEstimater		m_FPSMeasurer;

		HWND				m_hWnd;
		LPDIRECT3D9			m_pD3D;
		DirectXDevicePtr	m_pD3DDevice;
		LPD3DXFONT			m_pFont;
	public:
		GraphicSystem();
		~GraphicSystem();

		bool StartUp(BOOL windowed, HWND hWnd);
		void ShutDown();

		void Render();

		MAKE_GETSETTER(m_bDrawFPS, DrawFPS);
		MAKE_GETTER(m_hWnd, HWND);
		MAKE_GETTER(m_pD3DDevice, Device);
	};
}