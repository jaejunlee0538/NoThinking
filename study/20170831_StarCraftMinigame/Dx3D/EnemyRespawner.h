#pragma once
#include "GameObject.h"
namespace qwer
{
	class EnemyRespawner :
		public GameObject
	{
	public:
		EnemyRespawner();
		~EnemyRespawner();

	private:
		//int m_nMaxEnemies;
		HashedString m_enemyName;
	};
}

