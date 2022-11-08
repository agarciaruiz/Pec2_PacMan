#ifndef TILEMAP_H
#define TILEMAP_H
#define TILESET_TILES  30

#include <iostream>
#include "raylib.h"

class Tilemap 
{
private:

    Rectangle tilesetRecs[TILESET_TILES] = {
    { 0, 0, 32, 32 }, { 32, 0, 32, 32 },        // 1, 2
    { 64, 0, 32, 32 }, { 0, 32, 32, 32 },       // 3, 4
    { 32, 32, 32, 32 }, { 64, 32, 32, 32 },     // 5, 6
    { 0, 64, 32, 32 }, { 32, 64, 32, 32 },      // 7, 8
    { 64, 64, 32, 32 }, { 96, 0, 32, 32 },      // 9, 10
    { 128, 0, 32, 32 }, { 160, 0, 32, 32 },     // 11, 12
    { 96, 32, 32, 32 }, { 96, 64, 32, 32 },     // 13, 14
    { 160, 32, 32, 32 }, { 96, 64, 32, 32 },    // 15, 16
    { 128, 64, 32, 32 }, { 160, 64, 32, 32 },   // 17, 18
    { 192, 0, 32, 32 }, { 192, 32, 32, 32 },    // 19, 20
    { 192, 64, 32, 32 }, { 224, 0, 32, 32 },    // 21, 22
    { 256, 0, 32, 32 }, { 288, 0, 32, 32 },     // 23, 24
    { 224, 32, 32, 32 }, { 256, 32, 32, 32 },   // 25, 26
    { 288, 32, 32, 32 }, { 224, 64, 32, 32 },   // 27, 28
    { 256, 62, 32, 32 }, { 288, 64, 32, 32 },   // 29, 30
    };

	struct Tile
	{
		int value;
        int object;
		bool collider;
		Color color;
	};

	Tile* _tiles;
	int _tileCountX;
	int _tileCountY;
	int _tileSize;
    Vector2 _position;

public:
    Vector2 Tilemap::Position() const;
    int Tilemap::TileSize() const;

	void Tilemap::Load(const char* valuesMap, const char* collidersMap, const char* objectsMap);
    void Tilemap::Init(float scrW, float scrH, int tileSize);
	void Tilemap::Unload();
	void Tilemap::Draw(Texture2D tileset);
};

#endif