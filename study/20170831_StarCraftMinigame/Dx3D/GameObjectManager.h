#pragma once
#include "Singleton.h"
#include <unordered_map>
namespace qwer
{
	class GameObject;
	class GameObjectManager : public Singleton<GameObjectManager>
	{
	public:
		GameObjectManager();
		~GameObjectManager();
		
		static std::unordered_map<HashedString, GameObject*> m_objectsByName;
		static std::multimap<HashedString, GameObject*> m_objectsByTag;
	};
}
