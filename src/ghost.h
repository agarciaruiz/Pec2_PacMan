#ifndef GHOST_H
#define GHOST_H
#include "raylib.h"
#include "global.h"
#include "tilemap.h"
#include "player.hpp"
#include <vector>

class Ghost
{
private:
	float _speed;
	Vector2 _position;
	Vector2 _dir;
	Vector2 _initialTile;
	Vector2 _tile;
	Vector2 _targetTile {};
	Rectangle _frameRec;
	Image _image;
	Texture2D _currentTexture;
	Rectangle _bounds;

	Tilemap* _tilemap;
	Player* _player;

	float _frightenedCounter;
	float _frightenedTimeout;

	enum State { CHASE, FRIGHTENED, EATEN};
	State _currentState = CHASE;


	Rectangle Ghost::GetBounds();
	void Ghost::CheckState();
	void Ghost::Move();
	std::vector<Vector2> Ghost::CheckCollisions(std::vector<Vector2> directions);
	Vector2 Ghost::CheckDistanceWithTarget(Vector2 target, std::vector<Vector2> directions);
	bool Ghost::CheckCollisionWithPlayer();
	void Ghost::ResetPosition();
	Vector2 Ghost::GetNewDirection();

public:
	Vector2 Ghost::Position() const;
	Rectangle Ghost::Bounds() const;

	Ghost::Ghost();
	void Ghost::Init();
	void Ghost::Update();
	void Ghost::Draw();
	void Ghost::Reset();
};
#endif