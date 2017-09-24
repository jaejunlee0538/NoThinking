#include "stdafx.h"
#include "GraphicSystem.h"
#include <NT_Logging\Logger.h>
#include <NT_Common\MacroUtils.h>
#include <NT_Common\TimeManager.h>
namespace qwer {
	GraphicSystem::GraphicSystem()
		:m_HWND(0), m_D3D(NULL), m_D3DDevice(NULL), m_FPSMeasurer(1.0f)
	{
	}

	GraphicSystem::~GraphicSystem()
	{
	}

	bool GraphicSystem::StartUp(BOOL windowed, HWND hWnd)
	{
		m_HWND = hWnd;

		m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

		UINT adapterNum = -1;
		//내꺼에서는 하나밖에 안뜨네...(내장 아니면 외장)
		UINT nAdapters = m_D3D->GetAdapterCount();
		if (nAdapters <= 0) {
			LOG_ERROR(Logging::CHANNEL_CORE, "사용가능한 어댑터가 없습니다.");
			return false;
		}

		std::vector<D3DADAPTER_IDENTIFIER9> adapterIdentifiers(nAdapters);
		for (int i = 0; i < nAdapters; ++i) {
			m_D3D->GetAdapterIdentifier(i, 0, &adapterIdentifiers[i]);
			LOG_INFO(Logging::CHANNEL_CORE, "Adapter %d : %s", i, adapterIdentifiers[i].DeviceName);
			LOG_INFO(Logging::CHANNEL_CORE, "Adapter %d Desc : %s", i, adapterIdentifiers[i].Description);
		}


		adapterNum = 0;

		std::vector<D3DFORMAT> fmtArr = { D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5,D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5 };
		std::vector<D3DDEVTYPE> devArr = { D3DDEVTYPE_HAL ,D3DDEVTYPE_HAL ,D3DDEVTYPE_HAL,D3DDEVTYPE_REF,D3DDEVTYPE_REF,D3DDEVTYPE_REF };

		size_t iConfig;
		for (iConfig = 0; iConfig < fmtArr.size(); ++iConfig) {
			if (SUCCEEDED(m_D3D->CheckDeviceType(adapterNum, devArr[iConfig], fmtArr[iConfig], fmtArr[iConfig], windowed))) {
				break;
			}
		}

		if (iConfig >= fmtArr.size()) {
			LOG_ERROR(Logging::CHANNEL_CORE, "적절한 디바이스를 찾지 못했습니다.");
			return false;
		}

		switch (devArr[iConfig]) {
		case D3DDEVTYPE_HAL:
			LOG_INFO(Logging::CHANNEL_CORE, "DeviceType : HAL");
			break;
		case D3DDEVTYPE_REF:
			LOG_INFO(Logging::CHANNEL_CORE, "DeviceType : REF");
			break;
		}

		switch (fmtArr[iConfig]) {
		case D3DFMT_X8R8G8B8:
			LOG_INFO(Logging::CHANNEL_CORE, "AdapterFormat : X8R8G8B8");
			break;
		case D3DFMT_X1R5G5B5:
			LOG_INFO(Logging::CHANNEL_CORE, "AdapterFormat : X1R5G5B5");
			break;
		case D3DFMT_R5G6B5:
			LOG_INFO(Logging::CHANNEL_CORE, "AdapterFormat : R5G6B5");
			break;
		}

		D3DCAPS9 stCaps;
		int nVertexProcessing;

		m_D3D->GetDeviceCaps(adapterNum, devArr[iConfig], &stCaps);

		if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
			LOG_INFO(Logging::CHANNEL_CORE, "Vertex Processing : Hardware");
			nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
#ifdef NDEBUG
			if (stCaps.DevCaps & D3DDEVCAPS_PUREDEVICE) {
				//속도는 빠르지만 디버깅할 떄 안좋음.
				LOG_INFO(Logging::CHANNEL_CORE, "Enable PureDevice");
				nVertexProcessing |= D3DCREATE_PUREDEVICE;
			}
#endif
		}
		else {
			LOG_INFO(Logging::CHANNEL_CORE, "Vertex Processing : Software");
			nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		//TODO : 이게 뭐지?
		int presentInterval = D3DPRESENT_INTERVAL_DEFAULT;
		//if (stCaps.PresentationIntervals & D3DPRESENT_INTERVAL_FOUR) {
		//	presentInterval = D3DPRESENT_INTERVAL_FOUR;
		//}

		//깊이-스텐실 버퍼 포맷 
		D3DFORMAT depthstencil = D3DFMT_D24S8;
		if (FAILED(m_D3D->CheckDeviceFormat(adapterNum, devArr[iConfig], fmtArr[iConfig], D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, depthstencil))) {
			//게임 구현에 필요한 Depth-Stencil버퍼를 이요할 수 없기 때문에 게임을 실행할 수 없는건가?
			LOG_ERROR(Logging::CHANNEL_CORE, "Depth-Stencil format D24S8 unsupported.");
			return false;
		}

		//멀티 샘플링
		D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
		DWORD maxQuality = 0;
		for (int i = D3DMULTISAMPLE_2_SAMPLES; i < D3DMULTISAMPLE_16_SAMPLES; ++i) {
			D3DMULTISAMPLE_TYPE mst = (D3DMULTISAMPLE_TYPE)i;
			DWORD quality;
			if (SUCCEEDED(m_D3D->CheckDeviceMultiSampleType(adapterNum, devArr[iConfig], fmtArr[iConfig], windowed, mst, &quality))) {
				if (SUCCEEDED(m_D3D->CheckDeviceMultiSampleType(adapterNum, devArr[iConfig], depthstencil, windowed, mst, &quality))) {
					LOG_INFO(Logging::CHANNEL_CORE, "%d Sample Supported", mst);
					multiSampleType = mst;
					maxQuality = quality - 1;
				}
			}
		}

		//
		D3DDISPLAYMODE bestmode;
		UINT nAdapterMode = m_D3D->GetAdapterModeCount(adapterNum, fmtArr[iConfig]);
		assert(nAdapterMode > 0);
		m_D3D->EnumAdapterModes(adapterNum, fmtArr[iConfig], 0, &bestmode);
		for (UINT i = 1; i < nAdapterMode; i++)
		{
			D3DDISPLAYMODE dispmode;
			m_D3D->EnumAdapterModes(adapterNum, fmtArr[iConfig], i, &dispmode);
			if (dispmode.Width > bestmode.Width)
			{
				bestmode.Width = dispmode.Width;
				bestmode.Height = dispmode.Height;
				bestmode.RefreshRate = dispmode.RefreshRate;
				continue;
			}
			if (dispmode.Height > bestmode.Height)
			{
				bestmode.Height = dispmode.Height;
				bestmode.RefreshRate = dispmode.RefreshRate;
				continue;
			}
			if (dispmode.RefreshRate > bestmode.RefreshRate)
			{
				bestmode.RefreshRate = dispmode.RefreshRate;
				continue;
			}
		}
		LOG_INFO(Logging::CHANNEL_CORE, "Width X Height : %u X %u", bestmode.Width, bestmode.Height);
		LOG_INFO(Logging::CHANNEL_CORE, "RefreshRate : %u", bestmode.RefreshRate);

		D3DPRESENT_PARAMETERS stD3DPP;
		ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
		stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
		stD3DPP.Windowed = windowed;
		stD3DPP.BackBufferFormat = fmtArr[iConfig];
		stD3DPP.EnableAutoDepthStencil = TRUE;
		stD3DPP.AutoDepthStencilFormat = depthstencil;
		stD3DPP.PresentationInterval = presentInterval;
		stD3DPP.MultiSampleType = multiSampleType;
		stD3DPP.MultiSampleQuality = maxQuality;
		if (!windowed) {
			stD3DPP.BackBufferHeight = bestmode.Height;
			stD3DPP.BackBufferWidth = bestmode.Width;
			stD3DPP.FullScreen_RefreshRateInHz = bestmode.RefreshRate;
		}

		HRESULT ret = m_D3D->CreateDevice(adapterNum,
			devArr[iConfig],
			m_HWND,
			nVertexProcessing,
			&stD3DPP,
			&m_D3DDevice);
		if (FAILED(ret)) {
			LOG_ERROR(Logging::CHANNEL_CORE, "CreateDevice Error : %s", DXGetErrorDescriptionA(ret));
			return false;
		}

		return true;
	}

	void GraphicSystem::ShutDown()
	{
		if (m_D3DDevice) {
			ULONG nUnreleased = m_D3DDevice->Release();
			m_D3DDevice = NULL;
			if (nUnreleased > 0) {
				LOG_ERROR(Logging::CHANNEL_CORE, "%u Unreleased Resource", nUnreleased);
				LOG_FLUSH_LOG();
			}
			assert(nUnreleased == 0 && "반환되지 않은 리소스가 있습니다.");
		}
		SAFE_RELEASE(m_D3D);
	}

	void GraphicSystem::Render()
	{
		m_FPSMeasurer.update(GET_TIMEMANAGER().CurrentRealTime());

		m_D3DDevice->Clear(
			0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f, 0);
		m_D3DDevice->BeginScene();
		m_D3DDevice->EndScene();
		m_D3DDevice->Present(0, 0, 0, 0);
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
	DirectXDevicePtr GraphicSystem::GetDeivce() {
		return m_D3DDevice;
	}
}