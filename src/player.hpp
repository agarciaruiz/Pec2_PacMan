#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "screen.hpp"
#include "tilemap.h"

class Player {
private:
    Vector2 _position;
    Vector2 _dir;
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
    State _currentState = IDLE;

    Tilemap _tilemap;

    void Player::Move();
    void Player::CheckState();
    void Player::CheckCollisions(Vector2 oldPosition);

public:
    Vector2 Player::BasePosition() const;
    int Player::Score() const;
    int Player::Lifes() const;
    Texture2D Player::Texture() const;

    void Player::Init(Tilemap tilemap);
    void Player::Update();
    void Player::Draw();
    void Player::Reset();
};
#endif