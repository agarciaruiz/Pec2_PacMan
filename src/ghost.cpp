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
	_dir =	CheckDistanceWithPlayer(newDirections);
	_position.x += _dir.x * _speed;
	_position.y += _dir.y * _speed;
}

std::vector<Vector2> Ghost::CheckCollisions(std::vector<Vector2> directions)
{
	std::vector<Vector2> newDirections;
	for(auto it = directions.begin(); it != directions.end(); it++)
	{
		int tileX = ((_position.x - _tilemap.Position().x) / _tilemap.TileSize() ) + it->x;
		int tileY = ((_position.y - _tilemap.Position().y) / _tilemap.TileSize()) + it->y;

		if ((_tilemap.Tiles()[tileY * _tilemap.TileCountX() + tileX].collider) != 0)
		{
			newDirections.push_back({it->x, it->y});
		}
	}
	return newDirections;
}

Vector2 Ghost::CheckDistanceWithPlayer(std::vector<Vector2> directions)
{
	int playerTileX = ((_player.BasePosition().x - _tilemap.Position().x) / _tilemap.TileSize());
	int playerTileY = ((_player.BasePosition().y - _tilemap.Position().y) / _tilemap.TileSize());

	float currentDistance = 0;
	Vector2 resultingDir {};
	for (auto it = directions.begin(); it != directions.end(); it++) 
	{
		int ghostTileX = ((_position.x - _tilemap.Position().x) / _tilemap.TileSize()) + it->x;
		int ghostTileY = ((_position.y - _tilemap.Position().y) / _tilemap.TileSize()) + it->y;
		float distance = pow((playerTileX - ghostTileX), 2) + pow((playerTileY - ghostTileY), 2);

		if (distance > currentDistance)
		{
			currentDistance = distance;
			resultingDir = {it->x, it->y};
		}
	}
	return resultingDir;
}

Vector2 Ghost::Position() const { return _position; }
Rectangle Ghost::Bounds() const { return _bounds; }

void Ghost::Init(Tilemap tilemap, Player player)
{
    _tilemap = tilemap;
	_player = player;
	this->_position = Vector2{ tilemap.Position().x + 13 * tilemap.TileSize(), tilemap.Position().y + 9 * tilemap.TileSize() };
	_dir = {0, -1};
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