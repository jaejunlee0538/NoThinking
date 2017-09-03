#pragma once
#include <NT_Common/Singleton.h>

namespace qwer
{


	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool StartUp();
		void Shutdown();

		bool IsOnceKeyDown(int key, bool clearAfterRead = false);
		bool IsStayKeyDown(int key, bool clearAfterRead = false);

		void OnKeyDownMessage(int key);
		void OnKeyUpMessage(int key);
	};
}
