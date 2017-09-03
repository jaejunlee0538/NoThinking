#include "stdafx.h"
#include "LogTargetDebugStream.h"
#include <Windows.h>
namespace qwer {
	namespace Logging {
		LogTargetDebugStream::LogTargetDebugStream()
		{
		}

		LogTargetDebugStream::~LogTargetDebugStream()
		{
		}

		void LogTargetDebugStream::Log(const char * msg)
		{
			OutputDebugStringA(msg);
		}

		void LogTargetDebugStream::Shutdown()
		{
			this->Flush();
		}
	}
}