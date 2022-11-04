#include "enemy_manager.h"

int EnemyManager::LandedTroopers() const { return _landedTroopers; }
std::list<Helicopter*> EnemyManager::Helicopters() const { return _helicopters; }
std::list<Trooper*> EnemyManager::Troopers() const { return _troopers; }

void EnemyManager::Init()
{
	SetRandomSeed(time(NULL));
	helicopterSpawnTime = 3;
	timer = helicopterSpawnTime - 1;

	trooperTimer = 0;
	_landedTroopers = 0;
}

void EnemyManager::Update()
{
	// Helicopter spawn, move and destroy
	HelicopterRoutine();
	// Update && Destroy trooper
	TrooperRoutine();
}

void EnemyManager::Draw()
{
	DrawHelicopters();
	DrawTroopers();
}

void EnemyManager::Reset()
{
	_landedTroopers = 0;
	for(Helicopter* helicopter : _helicopters)
	{
		helicopter->Unload();
		helicoptersPool.ReturnItem(helicopter);
	}
	_helicopters.clear();

	for(Trooper* trooper : _troopers)
	{
		trooper->UnloadTextures();
		troopersPool.ReturnItem(trooper);
	}
	_troopers.clear();
}

Helicopter* EnemyManager::SpawnHelicopter()
{
	Helicopter* helicopter = new Helicopter();
	helicopter->Init();
	return helicopter;
}

void EnemyManager::SpawnTrooper(Helicopter* helicopter)
{
	Trooper* trooper = troopersPool.GetItem();
	trooper->Init(helicopter->Position());
	_troopers.push_back(trooper);
	helicopter->DropTrooper();
}

void EnemyManager::HelicopterRoutine()
{
	timer += GetFrameTime();
	if (timer >= helicopterSpawnTime)
	{
		Helicopter* helicopter = helicoptersPool.GetItem();
		helicopter->Init();
		_helicopters.push_back(helicopter);
		helicopterSpawnTime = GetRandomValue(3, 5);
		timer = 0;
	}
	MoveHelicopters();
}

void EnemyManager::MoveHelicopters()
{
	std::list<Helicopter*>::iterator it = _helicopters.begin();
	while (it != _helicopters.end())
	{
		Helicopter* helicopter = (*it);
		if (helicopter->IsAlive() || !helicopter->OutOfScreen())
		{
			if (helicopter->HasTrooper() && helicopter->TimeOut())
			{
				SpawnTrooper(helicopter);
			}
			helicopter->Move();
			++it;
		}
		else
		{
			if (helicopter->TextureReloaded())
			{
				helicopter->Unload();
				helicoptersPool.ReturnItem(helicopter);
				_helicopters.erase(it++);
			}
		}
	}
}

void EnemyManager::TrooperRoutine()
{
	std::list<Trooper*>::iterator it = _troopers.begin();
	while(it != _troopers.end())
	{
		Trooper* trooper = (*it);
		if(trooper->IsAlive() || !trooper->IsGrounded())
		{
			trooper->Fall();
			if(trooper->IsGrounded() && !trooper->previouslyGrounded)
			{
				_landedTroopers++;
				trooper->PreviouslyGrounded(true);
			}
			++it;
		}
		else
		{
			if(trooper->TextureReloaded())
			{
				trooper->UnloadTextures();
				troopersPool.ReturnItem(trooper);
				_troopers.erase(it++);
			}
		}
	}
}

void EnemyManager::DrawHelicopters()
{
	for(Helicopter* helicopter : _helicopters)
	{
		helicopter->Draw();
	}
}

void EnemyManager::DrawTroopers()
{
	for(Trooper* trooper : _troopers)
	{
		trooper->Draw();
	}
}