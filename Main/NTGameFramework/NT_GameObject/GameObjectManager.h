#pragma once
#include <NT_Common\Singleton.h>
#include <NT_Common\HashedString.h>
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
