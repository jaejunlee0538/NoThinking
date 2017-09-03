#pragma once
#include "Singleton.h"
namespace qwer {
	typedef LPDIRECT3DDEVICE9 DirectXDevicePtr;

	class GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		GraphicSystem();
		~GraphicSystem();

		bool StartUp(BOOL windowed, HWND hWnd);
		void ShutDown();

		DirectXDevicePtr GetDevice();

	private:
		HWND m_hWnd;
		LPDIRECT3D9			m_pD3D;
		LPDIRECT3DDEVICE9	m_pD3DDevice;
	};
}