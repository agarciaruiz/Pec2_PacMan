#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_LIFES             5

#include <vector>
#include <math.h>
#include "raylib.h"
#include "screen.hpp"
#include "bullet.h"
#include "helicopter.h"
#include "pool.h"

class Player {
private:
    Vector2 _position;
    float _moveSpeed;
    int _score;
    int _lifes;

    Texture2D _texture;
    void Player::Move(Vector2 dir);

public:
    Vector2 Player::BasePosition() const;
    int Player::Score() const;
    int Player::Lifes() const;
    Texture2D Player::Texture() const;

    Player::Player();
    void Player::Init();
    void Player::Update();
    void Player::Draw();
    void Player::Reset();
};
#endif