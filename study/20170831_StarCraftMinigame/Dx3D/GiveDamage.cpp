#include "stdafx.h"
#include "GiveDamage.h"
namespace Messaging {
	GiveDamage::GiveDamage(int damage)
		:Message(MessageTypes::GIVE_DAMAGE)
	{
	}

	GiveDamage::~GiveDamage()
	{
	}
}