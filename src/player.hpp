#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "screen.hpp"
#include "tilemap.h"

class Player {
private:
    Vector2 _position;
    float _moveSpeed;
    int _score;
    int _lifes;

    Image _image;
    Texture2D _texture;
    Rectangle _frameRec;

    int _currentFrame;
    int _framesCounter;
    int _framesSpeed;

    enum State {IDLE, RIGHT, LEFT, DOWN, UP, DEAD};
    State currentState = IDLE;

    void Player::Move(Vector2 dir);
    void Player::CheckState();

public:
    Vector2 Player::BasePosition() const;
    int Player::Score() const;
    int Player::Lifes() const;
    Texture2D Player::Texture() const;

    void Player::Init();
    void Player::Update();
    void Player::Draw();
    void Player::Reset();
};
#endif