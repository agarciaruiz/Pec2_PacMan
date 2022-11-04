#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "helicopter.h"
#include "trooper.h"
#include "pool.h"

class EnemyManager
{
private:
	// Helicopter settings
	Pool<Helicopter> helicoptersPool {};
	std::list<Helicopter*> _helicopters {};
	float timer;
	float helicopterSpawnTime;

	// Trooper settings
	Pool<Trooper> troopersPool{};
	std::list<Trooper*> _troopers{};
	float trooperTimer;
	int _landedTroopers;

	Helicopter* EnemyManager::SpawnHelicopter();
	void EnemyManager::SpawnTrooper(Helicopter* helicopter);

	void EnemyManager::HelicopterRoutine();
	void EnemyManager::MoveHelicopters();
	void EnemyManager::TrooperRoutine();

	void EnemyManager::DrawHelicopters();
	void EnemyManager::DrawTroopers();

public:
	int EnemyManager::LandedTroopers() const;
	std::list<Helicopter*> EnemyManager::Helicopters() const;
	std::list<Trooper*> EnemyManager::Troopers() const;

	void EnemyManager::Init();
	void EnemyManager::Update();
	void EnemyManager::Draw();
	void EnemyManager::Reset();
};

#endif