#pragma once
#include "Message.h"
namespace Messaging {
	class GiveDamage :
		public Message
	{
	public:
		GiveDamage(int damage);
		~GiveDamage();

		int GetDamage() const {
			return m_damage;
		}
	private:
		int m_damage;
	};
}

