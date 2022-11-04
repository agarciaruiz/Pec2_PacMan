#include "bullet.h"

bool Bullet::HelicopterHit() const { return _helicopterHit; }
bool Bullet::TrooperHit() const { return _trooperHit; }
Vector2 Bullet::Direction() const { return _direction; }

void Bullet::Init(Vector2 position, Vector2 direction)
{
	_position = position;
	_direction = direction;
	_radius = 1;
	_speed = 5;
	_helicopterHit = false;
	_trooperHit = false;
}

void Bullet::Update(std::list<Helicopter*> helicopters, std::list<Trooper*> troopers)
{
	for(Helicopter* helicopter : helicopters)
	{
		if (helicopter->IsAlive() && CheckCollisionCircleRec(_position, _radius, helicopter->Bounds()))
		{
			_helicopterHit = true;
			helicopter->Destroy();
		}
	}

	for (Trooper* trooper : troopers)
	{
		if (trooper->IsAlive() && CheckCollisionCircleRec(_position, _radius, trooper->Bounds()))
		{
			_trooperHit = true;
			trooper->Destroy();
		}
	}

	_position.x += _direction.x * _speed;
	_position.y -= _direction.y * _speed;
}

bool Bullet::IsOutOfScreen()
{
	if (_position.x >= SCR_WIDTH || _position.x <= 0 || _position.y <= 0)
	{
		return true;
	}
	return false;
}

void Bullet::Draw()
{
	DrawText(".", _position.x, _position.y, 40, WHITE);
}