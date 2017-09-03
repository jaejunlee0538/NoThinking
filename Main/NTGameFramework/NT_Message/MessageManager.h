#pragma once
#include <NT_Common/Singleton.h>

namespace qwer
{
	class MessageManager : public Singleton<MessageManager>
	{
	public:
		MessageManager();
		~MessageManager();
	};
}