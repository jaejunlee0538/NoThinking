#pragma once
#include <NT_Common/Singleton.h>

namespace qwer
{
	class PhysicsSystem :
		public Singleton<PhysicsSystem>
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();
	};
}
