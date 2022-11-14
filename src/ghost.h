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
	Vector2 _tile;
	Vector2 _targetTile {};
	Rectangle _frameRec;
	Image _image;
	Texture2D _currentTexture;
	Rectangle _bounds;
	Tilemap _tilemap;
	Player *_player;

	enum State { CHASE, FRIGHTENED, EATEN};
	State _currentState = CHASE;

	Rectangle Ghost::GetBounds();
	void Ghost::CheckState();
	void Ghost::Move();
	std::vector<Vector2> Ghost::CheckCollisions(std::vector<Vector2> directions);
	Vector2 Ghost::CheckDistanceWithPlayer(std::vector<Vector2> directions);

public:
	Vector2 Ghost::Position() const;
	Rectangle Ghost::Bounds() const;

	void Ghost::Init(Tilemap tilemap, Player *player);
	void Ghost::Update();
	void Ghost::Draw();
	void Ghost::UnloadTextures();
};
#endif