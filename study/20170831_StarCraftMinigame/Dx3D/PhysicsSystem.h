#pragma once
#include "Singleton.h"

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
