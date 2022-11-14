#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "pool.h"
#include "ghost.h"
#include "tilemap.h"
#include "player.hpp"

class EnemyManager
{
private:
	Ghost _ghost;
	Player _player;
public:

	void EnemyManager::Init(Tilemap tilemap);
	void EnemyManager::Update();
	void EnemyManager::Draw();
	void EnemyManager::Reset();
};

#endif