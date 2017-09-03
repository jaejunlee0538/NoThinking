#include "stdafx.h"
#include "Logger.h"
#include <NT_Common/TimeManager.h>

namespace qwer {
	namespace Logging {
		const char * GetChannelString(Channels channel)
		{
			switch (channel) {
			case CHANNEL_GENERAL:
				return "GENERAL";
			case CHANNEL_CORE:
				return "CORE";
			case CHANNEL_SOUND:
				return "SOUND";
			default:
				assert(false && "���ǵ��� ���� ä���Դϴ�.");
			}
		}

		const char * GetVerbosityString(VerbosityLevel verbosity)
		{
			switch (verbosity) {
			case LEVEL_DEBUG:
				return "DEBUG";
			case LEVEL_VERBOSE:
				return "VERBOSE";
			case LEVEL_INFO:
				return "INFO";
			case LEVEL_WARN:
				return "WARN";
			case LEVEL_ERROR:
				return "ERROR";
			case LEVEL_FATAL:
				return "FATAL";
			default:
				assert(false && "���ǵ��� ���� Verbose�����Դϴ�.");
			}
		}

		Logger::Logger()
			:m_numLogTargets(0)
		{

		}

		Logger::~Logger()
		{
			Shutdown();
		}

		bool Logger::StartUp() {
			memset(m_logTargets, 0, sizeof(m_logTargets[0])*MAX_NUM_TARGETS);
			EnableChannel(CHANNEL_GENERAL, true);
			SetVerbosity(LEVEL_INFO);
			return true;
		}

		void Logger::Shutdown() {
			for (int i = 0; i < m_numLogTargets; ++i) {
				m_logTargets[i]->Shutdown();
			}
			m_numLogTargets = 0;
		}

		bool Logger::AddLogTarget(ILogTarget * target)
		{
			if (m_numLogTargets >= MAX_NUM_TARGETS) {
				return false;
			}
			m_logTargets[m_numLogTargets++] = target;
			return true;
		}

		void Logger::EnableChannel(Channels channel, bool enable)
		{
			if (enable) {
				m_channelBits |= 1 << channel;
			}
			else {
				m_channelBits &= ~(1 << channel);
			}
		}

		bool Logger::IsChannelEnabled(Channels channel) const
		{
			return m_channelBits | (1 << channel);
		}

		void Logger::SetVerbosity(VerbosityLevel verbosity)
		{
			m_verbosity = verbosity;
		}

		VerbosityLevel Logger::GetVerbosity() const
		{
			return m_verbosity;
		}

		void Logger::Flush()
		{
			for (size_t i = 0; i < m_numLogTargets; ++i) {
				m_logTargets[i]->Flush();
			}
		}

		void Logger::Log(Channels channel, VerbosityLevel verbosity, const char * fmt, ...)
		{
			if (IsChannelEnabled(channel) && m_numLogTargets > 0) {
				char msgBuffer[BUFFER_SIZE];
				int count = sprintf_s(msgBuffer, BUFFER_SIZE, "%.3lf %s %s %u \"",
					TimeManager::GetSingleton().CurrentRealTime(),
					GetVerbosityString(verbosity),
					GetChannelString(channel),
					TimeManager::GetSingleton().FramesCount());

				va_list args;
				va_start(args, fmt);
				int count2 = _vsnprintf_s(&msgBuffer[count], BUFFER_SIZE - count, BUFFER_SIZE - count - 3, fmt, args);
				va_end(args);
				msgBuffer[count + count2] = '\"';
				msgBuffer[count + count2 + 1] = '\n';
				msgBuffer[count + count2 + 2] = NULL;

				for (size_t i = 0; i < m_numLogTargets; ++i) {
					m_logTargets[i]->Log(msgBuffer);
				}
			}
		}
	}
}