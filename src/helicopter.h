#ifndef HELICOPTER_H
#define HELICOPTER_H
#include <time.h>
#include <stdlib.h>
#include <list>
#include "global.h"
#include "raylib.h"

class Helicopter
{
private:
	// Helicopter vars
	Rectangle _bounds;
	Vector2 _position;
	Texture2D _texture;
	Texture2D _leftCopterTexture;
	Texture2D _rightCopterTexture;
	float _speed;
	bool _leftSided;
	bool _isAlive;
	Sound _explosion;

	float _reloadTextureTimer;
	bool _textureReloaded;

	// Trooper vars
	float _spawnTimeout;
	float _spawnTimer;
	bool _timeOut;
	bool _hasTrooper;

	Rectangle Helicopter::GetBounds();
	void Helicopter::RecenterTexture();
	float Helicopter::RandomSide();
	Texture2D Helicopter::GetTextureFromSide(float side);
	Vector2 Helicopter::StartingPos();
	void Helicopter::SetSide();
	void Helicopter::ReloadTexture();

public:
	Rectangle Helicopter::Bounds() const;
	Vector2 Helicopter::Position() const;
	bool Helicopter::IsAlive() const;
	bool Helicopter::HasTrooper() const;
	bool Helicopter::TimeOut() const;
	bool Helicopter::TextureReloaded() const;
	bool Helicopter::OutOfScreen();

	void Helicopter::Init();
	void Helicopter::Move();
	void Helicopter::DropTrooper();
	void Helicopter::Draw();
	void Helicopter::Destroy();
	void Helicopter::Unload();
};

#endif // !HELICOPTER_H

