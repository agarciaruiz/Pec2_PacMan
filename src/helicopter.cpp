#include "helicopter.h"

// Getters
Rectangle Helicopter::Bounds() const { return _bounds; }
Vector2 Helicopter::Position() const { return _position; }
bool Helicopter::IsAlive() const { return _isAlive; }
bool Helicopter::HasTrooper() const { return _hasTrooper; }
bool Helicopter::TimeOut() const { return _timeOut; };
bool Helicopter::TextureReloaded() const { return _textureReloaded; };

float Helicopter::RandomSide()
{
	srand(time(NULL));
	int r = rand() % 2;
	if (r == 0)
		return 0;
	else
		return SCR_WIDTH;
}

Texture2D Helicopter::GetTextureFromSide(float side)
{
	if (side == 0)
	{
		_leftCopterTexture = LoadTexture("resources/Enemies/Helicopter_Left.png");
		return _leftCopterTexture;
	}
	else
	{
		_rightCopterTexture = LoadTexture("resources/Enemies/Helicopter_Right.png");
		return _rightCopterTexture;
	}
}

Rectangle Helicopter::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
}

void Helicopter::RecenterTexture()
{
	_position.x += _bounds.width / 2 - _texture.width / 2;
	_position.x += _bounds.height / 2 - _texture.height / 2;
}

Vector2 Helicopter::StartingPos()
{
	float randomHeight = GetRandomValue(SCR_HEIGHT / 3, SCR_HEIGHT / 8);
	return Vector2{ RandomSide(), randomHeight };
}

void Helicopter::SetSide()
{
	if (_position.x == 0)
		_leftSided = true;
	else
		_leftSided = false;
}

void Helicopter::Init()
{
	this->_position = StartingPos();
	this->_speed = GetRandomValue(3, 4);
	this->_texture = GetTextureFromSide(_position.x);
	_spawnTimeout = GetRandomValue(1, 3);
	SetSide();
	_isAlive = true;
	_bounds = GetBounds();
	_hasTrooper = true;

	_reloadTextureTimer = 0;
	_textureReloaded = false;
	_spawnTimer = 0;
	_timeOut = false;

	_explosion = LoadSound("resources/Music/explosion.wav");
}

void Helicopter::Move()
{
	if(_isAlive)
	{
		// If is left side, moove right
		if (_leftSided)
			_position.x += _speed;
		else
			_position.x -= _speed;

		// Update bounds
		_bounds = GetBounds();

		// Trooper routine
		_spawnTimer += GetFrameTime();
		if (_hasTrooper && _spawnTimer >= _spawnTimeout)
		{
			_timeOut = true;
		}
	}
	else
	{
		ReloadTexture();
	}
}

void Helicopter::ReloadTexture()
{
	_reloadTextureTimer += GetFrameTime();
	if (_reloadTextureTimer >= 0.5f)
		_textureReloaded = true;
}

void Helicopter::DropTrooper()
{
	_hasTrooper = false;
}

bool Helicopter::OutOfScreen()
{
	if (_leftSided && _position.x >= SCR_WIDTH)
	{
		return true;
	}
	else if (!_leftSided && _position.x <= 0)
	{
		return true;
	}
	return false;
}

void Helicopter::Draw()
{
	if (_textureReloaded) return;
	DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
}

void Helicopter::Destroy()
{
	PlaySound(_explosion);
	_texture = LoadTexture("resources/Enemies/Dead.png");
	RecenterTexture();
	_isAlive = false;
}

void Helicopter::Unload()
{
	UnloadSound(_explosion);
	UnloadTexture(_texture);
}