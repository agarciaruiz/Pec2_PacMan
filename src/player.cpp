#include "player.hpp"

bool Player::IsDead() const { return _isDead; }
Vector2 Player::Position() const { return _position; }
int Player::Score() const { return _score; }
int Player::Lifes() const { return _lifes; }
Texture2D Player::Texture() const { return _texture; }

// PRIVATE METHODS
void Player::Move() 
{
    _position.x += _dir.x * _moveSpeed;
    _position.y += _dir.y * _moveSpeed;
}

void Player::CheckState() 
{
    switch (_currentState) 
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
            _frameRec.y = (float)_texture.height / 4;
            break;
        case UP:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 2 * ((float)_texture.height / 4);
            break;
        case DOWN:
            _frameRec.x = (float)_currentFrame * (float)_texture.width / 2;
            _frameRec.y = 3 * ((float)_texture.height/4);
            break;
        case DEAD:
            _deadFrameRec.x = (float)_currentFrame * (float)_deadTexture.width / 12;
            _deadFrameRec.y = 0;
            break;
    }
}

void Player::CheckCollisions(Vector2 oldPosition) 
{
    for (int y = 0; y < _tilemap.TileCountY(); y++)
    {
        for (int x = 0; x < _tilemap.TileCountX(); x++)
        {
            // COLLISION WITH BORDERS
            if ((_tilemap.Tiles()[y * _tilemap.TileCountX() + x].collider == 0) && CheckCollisionRecs(GetBounds(), _tilemap.GetBounds(x, y)))
            {
                _position = oldPosition;
            }

            // IF PLAYER IS IN THE SAME TILE AS AN OBJECT
            if (_position.x == _tilemap.Position().x + x * _tilemap.TileSize() && _position.y == _tilemap.Position().y + y * _tilemap.TileSize()) 
            {
                if ((_tilemap.Tiles()[y * _tilemap.TileCountX() + x].object == 30))
                {
                    _score += 10;
                    _tilemap.Tiles()[y * _tilemap.TileCountX() + x].object = -1;
                    _tilemap.numOfPills--;
                }
                else if((_tilemap.Tiles()[y * _tilemap.TileCountX() + x].object == 28))
                {
                    _score += 50;
                    _tilemap.Tiles()[y * _tilemap.TileCountX() + x].object = -1;
                    _tilemap.numOfPills--;
                }
            }
        }
    }
}


// PUBLIC METHODS
void Player::Init(Tilemap tilemap) 
{
    _score = 0;
    _tilemap = tilemap;
    _initialTile = { 13, 17 };
    _position = Vector2{tilemap.Position().x + _initialTile.x * tilemap.TileSize(), tilemap.Position().y + _initialTile.y * tilemap.TileSize()};
    _dir = Vector2{ 0, 0 };
    _moveSpeed = 2;
    _lifes = 3;
    _currentState = IDLE;
    _isDead = false;

    _image = LoadImage("resources/Game/PacMan.png");
    _texture = LoadTextureFromImage(_image);
    _frameRec = { 0.0f, 0.0f, (float)_texture.width / 2, (float)_texture.height / 4};

    _deadImage = LoadImage("resources/Game/PacManDead.png");
    _deadTexture = LoadTextureFromImage(_deadImage);
    _deadFrameRec = { 0.0f, 0.0f, (float)_deadTexture.width / 12, (float)_deadTexture.height};

    _currentFrame = 0;
    _framesCounter = 0;
    _framesSpeed = 8;
}

Rectangle Player::GetBounds()
{
    return Rectangle{ _position.x, _position.y, (float)_texture.width / 2, (float)_texture.height / 4 };
}

void Player::Update()
{
    _framesCounter++;
    Vector2 oldPosition = _position;

    if (_framesCounter >= (60 / _framesSpeed)) 
    {
        _framesCounter = 0;
        _currentFrame++;

        if(_currentState != DEAD)
        {
            if (_currentFrame > 1) _currentFrame = 0;
        }
        else 
        {
            if (_currentFrame > 11)
            {
                _currentFrame = 0;
                _dir = { 0, 0 };
                _position = Vector2{ _tilemap.Position().x + _initialTile.x * _tilemap.TileSize(), _tilemap.Position().y + _initialTile.y * _tilemap.TileSize() };
                _currentState = IDLE;
                _isDead = false;
            }
        }

        CheckState();
    }

    if (_currentState == DEAD) return;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        _dir = { -1, 0 };
        _currentState = LEFT;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        _dir = { 1, 0 };
        _currentState = RIGHT;
    }
    else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        _dir = { 0, 1 };
        _currentState = DOWN;
    }
    else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        _dir = { 0, -1 };
        _currentState = UP;
    }

    Move();
    CheckCollisions(oldPosition);
}

void Player::Die() 
{
    if (_currentState == DEAD) return;

    _isDead = true;
    _currentState = DEAD;
    _lifes--;
}

void Player::Draw()
{
    if(_currentState != DEAD)
        DrawTextureRec(_texture, _frameRec, _position, WHITE);
    else
        DrawTextureRec(_deadTexture, _deadFrameRec, _position, WHITE);
}

void Player::Reset()
{
    UnloadImage(_image);
    UnloadTexture(_texture);
    UnloadImage(_deadImage);
    UnloadTexture(_deadTexture);


    _score = 0;
}