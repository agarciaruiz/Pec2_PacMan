#include "ghost.h"

Rectangle Ghost::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_currentTexture.width / 12, (float)_currentTexture.height / 4};
}

Ghost::Ghost(){}

void Ghost::CheckState() 
{
	switch (_currentState)
	{
		case CHASE:
			_frameRec.x = 0;
			_frameRec.y = 0;
			if(!_player->IsDead())
				Move();
			break;
		case FRIGHTENED:
			_frameRec.x = 8 * (float)_currentTexture.width / 12;
			_frameRec.y = 0;
			Move();
			break;
		case EATEN:
			_frameRec.x = 8 * (float)_currentTexture.width / 12;
			_frameRec.y = (float)_currentTexture.height / 4;
			Move();
			break;
	}
}

void Ghost::Move()
{
	std::vector<Vector2> possibleDirections;
	if (_dir.x == 0 && _dir.y == 1) 
		possibleDirections = { {-1, 0}, {0, 1}, {1, 0} };
	else if(_dir.x == 0 && _dir.y == -1)
		possibleDirections = { {-1, 0}, {0, -1}, {1, 0} };
	else if(_dir.x == 1 && _dir.y == 0)
		possibleDirections = { {1, 0}, {0, -1}, {0, 1} };
	else if(_dir.x == -1 && _dir.y == 0)
		possibleDirections = { {-1, 0}, {0, -1}, {0, 1} };

	std::vector<Vector2> newDirections = CheckCollisions(possibleDirections);

	Vector2 newDir{};
	if (_currentState == CHASE)
	{
		Vector2 target = { 
			((_player->Position().x - _tilemap->Position().x) / _tilemap->TileSize()), 
			((_player->Position().y - _tilemap->Position().y) / _tilemap->TileSize()) 
		};
		newDir = CheckDistanceWithTarget(target, newDirections);
	}
	else if (_currentState == FRIGHTENED)
	{
		Vector2 target = { 25, 1 };
		newDir = CheckDistanceWithTarget(target, newDirections);
	}
	else if (_currentState == EATEN)
	{
		newDir = CheckDistanceWithTarget(_initialTile, newDirections);
	}

	_position.x += newDir.x * _speed;
	_position.y += newDir.y * _speed;

	Vector2 targetPos = { _tilemap->Position().x + _targetTile.x * _tilemap->TileSize(), _tilemap->Position().y + _targetTile.y * _tilemap->TileSize() };
	if (_position.x == targetPos.x && _position.y == targetPos.y)
	{
		_tile = _targetTile;
		_dir = newDir;
	}

	if (_currentState == CHASE && CheckCollisionWithPlayer())
		_player->Die();
	else if(_currentState == FRIGHTENED && CheckCollisionWithPlayer())
	{
		_currentState = EATEN;
		_player->GhostEaten();
	}

}

std::vector<Vector2> Ghost::CheckCollisions(std::vector<Vector2> directions)
{
	std::vector<Vector2> newDirections;
	for(auto it = directions.begin(); it != directions.end(); it++)
	{
		int tileX = _tile.x + it->x;
		int tileY = _tile.y + it->y;

		if ((_tilemap->Tiles()[tileY * _tilemap->TileCountX() + tileX].collider) != 0)
		{
			newDirections.push_back({it->x, it->y});
		}
	}
	return newDirections;
}

Vector2 Ghost::CheckDistanceWithTarget(Vector2 target, std::vector<Vector2> directions)
{
	float currentDistance = INFINITY;
	Vector2 dir{};
	for (auto it = directions.begin(); it != directions.end(); it++)
	{
		int ghostNewTileX = _tile.x + it->x;
		int ghostNewTileY = _tile.y + it->y;
		float distance = pow((target.x - ghostNewTileX), 2) + pow((target.y - ghostNewTileY), 2);
		if (distance < currentDistance)
		{
			currentDistance = distance;
			dir = { it->x, it->y };
			_targetTile = { _tile.x + it->x, _tile.y + it->y };
		}
	}
	return dir;
}

bool Ghost::CheckCollisionWithPlayer() 
{
	if(CheckCollisionRecs(GetBounds(), _player->GetBounds()))
	{
		if(_currentState == CHASE)
			ResetPosition();
		return true;
	}
	return false;
}

void Ghost::ResetPosition() 
{
	this->_position = Vector2{ _tilemap->Position().x + _initialTile.x * _tilemap->TileSize(), _tilemap->Position().y + _initialTile.y * _tilemap->TileSize() };
	_tile = _initialTile;
	_dir = { 0, -1 };
}

Vector2 Ghost::Position() const { return _position; }
Rectangle Ghost::Bounds() const { return _bounds; }

void Ghost::Init()
{
    _tilemap = Tilemap::GetInstance();
	_player = Player::GetInstance();

	_dir = {0, -1};
	_initialTile = { 13, 9 };
	_tile = _initialTile;
	this->_position = Vector2{ _tilemap->Position().x + _tile.x * _tilemap->TileSize(), _tilemap->Position().y + _tile.y * _tilemap->TileSize() };
	this->_bounds = GetBounds();

	_speed = 2;
	_frightenedCounter = 0;
	_frightenedTimeout = 10;

	_image = LoadImage("resources/Game/Enemies.png");
	_currentTexture = LoadTextureFromImage(_image);
	UnloadImage(_image);
	_frameRec = { 0.0f, 0.0f, (float)_currentTexture.width / 12, (float)_currentTexture.height / 4 };
}

void Ghost::Update()
{
	if (_player->BigPill()) 
	{
		_currentState = FRIGHTENED;
	}

	if (_currentState == FRIGHTENED && _currentState != EATEN) 
	{
		_frightenedCounter += GetFrameTime();
		if (_frightenedCounter >= _frightenedTimeout) 
		{
			_currentState = CHASE;
			_frightenedCounter = 0;
		}
	}
	else if (_currentState == EATEN) 
	{
		Vector2 initPos = { _tilemap->Position().x + _initialTile.x * _tilemap->TileSize(), _tilemap->Position().y + _initialTile.y * _tilemap->TileSize() };
		if (_position.x == initPos.x && _position.y == initPos.y) 
		{
			_currentState = CHASE;
		}
	}

	CheckState();
}

void Ghost::Draw()
{
	DrawTextureRec(_currentTexture, _frameRec, _position, WHITE);
}

void Ghost::Reset()
{
	UnloadTexture(_currentTexture);
}