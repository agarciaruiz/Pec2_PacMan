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

void Player::CheckState() 
{
    switch (currentState) 
    {
        case IDLE:
            _frameRec.x = 0;
            _frameRec.y = 0;
            break;
        case RIGHT:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 0;
            break;
        case LEFT:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 1;
            break;
        case UP:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 2;
            break;
        case DOWN:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 3;
            break;
        case DEAD:
            break;
    }
}

// PUBLIC METHODS
void Player::Init() 
{
    _score = 0;
    _position = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT / 2 };
    _moveSpeed = 2;
    _lifes = 3;
    _image = LoadImage("resources/Game/PacMan.png");
    _texture = LoadTextureFromImage(_image);
    _frameRec = { 0.0f, 0.0f, (float)_texture.width / 2, (float)_texture.height / 4};
    _position.x -= (float)_texture.width / 2;
    _position.y -= (float)_texture.height;

    _currentFrame = 0;
    _framesCounter = 0;
    _framesSpeed = 8;
}

void Player::Update()
{
    _framesCounter++;

    if (_framesCounter >= (60 / _framesSpeed)) 
    {
        _framesCounter = 0;
        _currentFrame++;

        if (_currentFrame > 5) _currentFrame = 0;

        CheckState();
    }


    Vector2 dir {};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
    {
        dir = { -1, 0 };
        currentState = LEFT;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        dir = { 1, 0 };
        currentState = RIGHT;
    }
    else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        dir = { 0, 1 };
        currentState = DOWN;
    }
    else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        dir = { 0, -1 };
        currentState = UP;
    }
    else 
    {
        currentState = IDLE;
        dir = { 0, 0 };
    }

    Move(dir);
}



void Player::Draw()
{
    DrawTextureRec(_texture, _frameRec, _position, WHITE);
    //DrawTexture(_texture, _position.x, _position.y, WHITE);
}

void Player::Reset()
{
    UnloadTexture(_texture);
    _score = 0;
}