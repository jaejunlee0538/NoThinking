#pragma once
#include "Singleton.h"

namespace qwer
{
	class MessageManager : public Singleton<MessageManager>
	{
	public:
		MessageManager();
		~MessageManager();
	};
}