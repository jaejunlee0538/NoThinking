#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <NT_Common/Singleton.h>
#include <NT_Common/FreqEstimater.h>
#include <NT_Common/MacroUtils.h>
namespace qwer {
	typedef LPDIRECT3DDEVICE9	DirectXDevicePtr;
	typedef LPDIRECT3DTEXTURE9	DirectXTexturePtr;
	class GraphicSystem : public Singleton<GraphicSystem>
	{
	private:
		bool				m_enableDrawFPS;
		FreqEstimater		m_FPSMeasurer;

		HWND				m_HWND;
		LPDIRECT3D9			m_D3D;
		DirectXDevicePtr	m_D3DDevice;
		LPD3DXFONT			m_font;
	public:
		GraphicSystem();
		~GraphicSystem();

		bool StartUp(BOOL windowed, HWND hWnd);
		void ShutDown();

		void Render();

		void EnableDrawFPS(bool enable);
		bool IsDrawFPSEnabled() const;

		HWND GetHWND();
		DirectXDevicePtr GetDeivce();
	};
}