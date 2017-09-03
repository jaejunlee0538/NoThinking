#pragma once
#include "Logger.h"
#include <fstream>
namespace qwer {
	namespace Logging {
		class LogTargetFile :
			public ILogTarget
		{
		public:
			LogTargetFile(const char* fileName);
			virtual ~LogTargetFile();
			void Log(const char* msg) override;
			void Flush() override;
			void Shutdown() override;
		private:
			std::ofstream m_file;
		};

	}
}