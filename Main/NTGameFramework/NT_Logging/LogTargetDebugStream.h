#pragma once
#include "Logger.h"
namespace qwer {
	namespace Logging {
		class LogTargetDebugStream :
			public ILogTarget
		{
		public:
			LogTargetDebugStream();
			virtual ~LogTargetDebugStream();
			void Log(const char* msg) override;
			void Flush() override {}
			void Shutdown() override;
		};
	}
}