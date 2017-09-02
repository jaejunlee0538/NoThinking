#include "stdafx.h"
#include "TimeManager.h"
namespace qwer {
	TimeManager::TimeManager()
		:m_deltaTimeGameOriginal(1.0)
		, m_gameTimeScale(1.0)
	{

	}

	TimeManager::~TimeManager()
	{
	}

	bool TimeManager::StartUp() {
		__int64 freq;
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&freq)) {
			m_highResolution = true;
			m_tickToSec = 1.0 / freq;
		}
		else {
			m_highResolution = false;
			m_tickToSec = 1e-3;
		}
		SetDesiredFPS(60);
		Reset();
		return true;
	}

	void TimeManager::Shutdown() {

	}

	void TimeManager::SetDesiredFPS(int fps)
	{
		assert(fps > 0);
		m_desiredFPS = fps;
		m_deltaTimeGameOriginal = 1.0 / m_desiredFPS;
		m_deltaGameTimeScaled = m_deltaTimeGameOriginal * m_gameTimeScale;
	}

	void TimeManager::SetFixedDeltatime(double deltaTime)
	{
		m_deltaTimeGameOriginal = deltaTime;
	}

	void TimeManager::SetGameTimeScale(double scale)
	{
		m_gameTimeScale = scale;
		m_deltaGameTimeScaled = m_deltaTimeGameOriginal * scale;
	}

	void TimeManager::Reset()
	{
		if (m_highResolution) {
			QueryPerformanceCounter((LARGE_INTEGER*)&m_tickBegin);
		}
		else {
			m_tickBegin = GetTickCount64();
		}

		SetGameTimeScale(1.0);
		m_currentTimeGame = 0.0f;
		m_deltaTimeReal = 0.0f;
		m_currentTimeReal = 0.0f;
		m_framesCount = 0;
	}

	void TimeManager::Update()
	{
		//FPS�� ���߱� ���� Sleep�Ѵ�.
		double currentTime;
		double desFrameTime = 1.0f / m_desiredFPS;
		GetCurrentTimeMS(currentTime);
		while (currentTime - m_currentTimeReal < desFrameTime*0.9) {
			::Sleep(1);
			GetCurrentTimeMS(currentTime);
		}

		//���� �ð��� �ʷ� ����Ѵ�.
		m_deltaTimeReal = currentTime - m_currentTimeReal;
		m_currentTimeReal = currentTime;

		//Game �ð� ������Ʈ
		m_currentTimeGame += m_deltaGameTimeScaled;
		m_framesCount++;
	}

	void TimeManager::GetCurrentTimeMS(double& currentTime)
	{
		__int64 tick;
		if (m_highResolution) {
			QueryPerformanceCounter((LARGE_INTEGER*)&tick);
			tick -= m_tickBegin;
		}
		else {
			tick = GetTickCount64();
			tick -= m_tickBegin;
		}
		currentTime = tick * m_tickToSec;
	}
}