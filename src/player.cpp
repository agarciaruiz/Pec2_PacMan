#include "player.hpp"

Vector2 Player::BasePosition() const { return _position; }
int Player::Score() const { return _score; }
int Player::Lifes() const { return _lifes; }
Texture2D Player::Texture() const { return _texture; }

// PRIVATE METHODS
void Player::Move(Vector2 dir) 
{
    _position.x += dir.x * _moveSpeed;
    _position.y += dir.y * _moveSpeed;
}


// PUBLIC METHODS
Player::Player() : _texture{ LoadTexture("resources/Player/PlayerBody.png") }, _score {0},
_position{ Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT } }, _moveSpeed {2}, _lifes{3}
{
    _position.x -= (float)_texture.width / 2;
    _position.y -= (float)_texture.height;
}

void Player::Update()
{
    Vector2 dir {};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        dir = { -1, 0 };
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        dir = { 1, 0 };
    else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        dir = { 0, -1 };
    else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        dir = { 0, 1 };
    else
        dir = { 0, 0 };

    Move(dir);
}

void Player::Draw()
{
    // Draw base
    DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
}

void Player::Reset()
{
    UnloadTexture(_texture);
    _score = 0;
}