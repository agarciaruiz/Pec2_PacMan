#include "ghost.h"

Rectangle Ghost::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_currentTexture.width / 12, (float)_currentTexture.height / 4};
}

void Ghost::CheckState() 
{
	switch (_currentState)
	{
		case CHASE:
			_frameRec.x = 0;
			_frameRec.y = 0;
			Move();
			break;
		case FRIGHTENED:
			_frameRec.x = 8 * (float)_currentTexture.width / 12;
			_frameRec.y = 0;
			break;
		case EATEN:
			_frameRec.x = 8 * (float)_currentTexture.width / 12;
			_frameRec.y = (float)_currentTexture.height / 4;
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
	Vector2 newDir = CheckDistanceWithPlayer(newDirections);

	_position.x += newDir.x * _speed;
	_position.y += newDir.y * _speed;

	Vector2 targetPos = { _tilemap.Position().x + _targetTile.x * _tilemap.TileSize(), _tilemap.Position().y + _targetTile.y * _tilemap.TileSize() };
	if (_position.x == targetPos.x && _position.y == targetPos.y)
	{
		_tile = _targetTile;
		_dir = newDir;
	}
}

std::vector<Vector2> Ghost::CheckCollisions(std::vector<Vector2> directions)
{
	std::vector<Vector2> newDirections;
	for(auto it = directions.begin(); it != directions.end(); it++)
	{
		int tileX = _tile.x + it->x;
		int tileY = _tile.y + it->y;

		if ((_tilemap.Tiles()[tileY * _tilemap.TileCountX() + tileX].collider) != 0)
		{
			newDirections.push_back({it->x, it->y});
		}
	}
	return newDirections;
}

Vector2 Ghost::CheckDistanceWithPlayer(std::vector<Vector2> directions)
{
	int playerTileX = ((_player->Position().x - _tilemap.Position().x) / _tilemap.TileSize());
	int playerTileY = ((_player->Position().y - _tilemap.Position().y) / _tilemap.TileSize());

	float currentDistance = INFINITY;
	Vector2 dir;
	for (auto it = directions.begin(); it != directions.end(); it++) 
	{
		int ghostNewTileX = _tile.x + it->x;
		int ghostNewTileY = _tile.y + it->y;
		float distance = pow((playerTileX - ghostNewTileX), 2) + pow((playerTileY - ghostNewTileY), 2);
		if (distance < currentDistance)
		{
			currentDistance = distance;
			dir = {it->x, it->y};
			_targetTile = { _tile.x + it->x, _tile.y + it->y };
		}
	}
	return dir;
}

Vector2 Ghost::Position() const { return _position; }
Rectangle Ghost::Bounds() const { return _bounds; }

void Ghost::Init(Tilemap tilemap, Player *player)
{
    _tilemap = tilemap;
	_player = player;
	_dir = {0, -1};
	_tile = { 13, 9 };
	this->_position = Vector2{ tilemap.Position().x + _tile.x * tilemap.TileSize(), tilemap.Position().y + _tile.y * tilemap.TileSize() };
	this->_bounds = GetBounds();
	_speed = 2;

	_image = LoadImage("resources/Game/Enemies.png");
	_currentTexture = LoadTextureFromImage(_image);
	_frameRec = { 0.0f, 0.0f, (float)_currentTexture.width / 12, (float)_currentTexture.height / 4 };
}

void Ghost::Update()
{
	CheckState();
}

void Ghost::Draw()
{
	DrawTextureRec(_currentTexture, _frameRec, _position, WHITE);
}

void Ghost::UnloadTextures()
{
	UnloadTexture(_currentTexture);
}