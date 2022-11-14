#include "enemy_manager.h"

void EnemyManager::Init(Tilemap tilemap)
{
	//_ghost.Init(tilemap, player);
}

void EnemyManager::Update()
{
	_ghost.Update();
}

void EnemyManager::Draw()
{
	_ghost.Draw();
}

void EnemyManager::Reset()
{

}
