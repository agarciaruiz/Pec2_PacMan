#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "screen.hpp"
#include "tilemap.h"

class Player {
private:
    static Player* _player;

    Vector2 _position;
    Vector2 _dir;
    Vector2 _initialTile;
    float _moveSpeed;
    int _score;
    int _lifes;
    bool _bigPill;
    bool _isDead;

    Image _image;
    Texture2D _texture;
    Rectangle _frameRec;

    Image _deadImage;
    Texture2D _deadTexture;
    Rectangle _deadFrameRec;

    int _currentFrame;
    int _framesCounter;
    int _framesSpeed;

    enum State {IDLE, RIGHT, LEFT, DOWN, UP, DEAD};
    State _currentState;

    Tilemap* _tilemap;


    Player::Player();
    void Player::Move();
    void Player::CheckState();
    void Player::CheckCollisions(Vector2 oldPosition);

public:
    bool Player::IsDead() const;
    Vector2 Player::Position() const;
    int Player::Score() const;
    int Player::Lifes() const;
    bool Player::BigPill() const;
    Texture2D Player::Texture() const;

    static Player* Player::GetInstance();
    void Player::Init();
    void Player::Update();
    void Player::Draw();
    void Player::Die();
    void Player::Reset();
    void Player::GhostEaten();
    Rectangle Player::GetBounds();
};
#endif