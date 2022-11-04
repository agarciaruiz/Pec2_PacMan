#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "raylib.h"
#include "helicopter.h"
#include "trooper.h"
#include "global.h"

class Bullet 
{
private:
	Vector2 _position;
	Vector2 _direction;
	float _speed;
	float _radius;
	bool _helicopterHit;
	bool _trooperHit;

public:
	bool Bullet::HelicopterHit() const;
	bool Bullet::TrooperHit() const;
	Vector2 Bullet::Direction() const;

	void Bullet::Init(Vector2 position, Vector2 direction);
	void Bullet::Update(std::list<Helicopter*> helicopters, std::list<Trooper*> troopers);
	bool Bullet::IsOutOfScreen();
	void Bullet::Draw();
};

#endif