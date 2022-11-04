#include "trooper.h"

Rectangle Trooper::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
}

bool Trooper::IsGrounded() const { return _isGrounded; }
void Trooper::PreviouslyGrounded(bool value) { previouslyGrounded = value; }
bool Trooper::IsAlive() const { return _isAlive; }
bool Trooper::TextureReloaded() const { return _textureReloaded; }
Vector2 Trooper::Position() const { return _position; }
Rectangle Trooper::Bounds() const { return _bounds; }

void Trooper::Init(Vector2 position)
{
	this->_position = position;
	this->_texture = LoadTexture("resources/Enemies/Soldier.png");
	this->_bounds = GetBounds();
	_speed = 2;
	_isGrounded = false;
	_isAlive = true;
	_reloadTextureTimer = 0;
	_textureReloaded = false;
	previouslyGrounded = false;
}

void Trooper::Fall()
{
	if (_isAlive)
	{
		if (_position.y < SCR_HEIGHT - _texture.height)
		{
			_position.y += _speed;
			_bounds = GetBounds();
		}
		else
		{
			_isGrounded = true;
			_position.y = SCR_HEIGHT - _texture.height;
		}
	}
	else
	{
		ReloadTexture();
	}
}

void Trooper::ReloadTexture()
{
	_reloadTextureTimer += GetFrameTime();
	if (_reloadTextureTimer >= 0.5f)
		_textureReloaded = true;
}

void Trooper::Draw()
{
	if (_textureReloaded) return;
	DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
}

void Trooper::Destroy()
{
	_texture = LoadTexture("resources/Enemies/Dead.png");
	_isAlive = false;
}

void Trooper::UnloadTextures()
{
	UnloadTexture(_texture);
}