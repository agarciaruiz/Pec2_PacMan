#ifndef TILEMAP_H
#define TILEMAP_H
#define TILESET_TILES  30

#include <iostream>
#include "raylib.h"

class Tilemap 
{
private:

    Rectangle tilesetRecs[TILESET_TILES] = {
    { 0, 0, 30, 30 }, { 30, 0, 30, 30 },        // 1, 2
    { 60, 0, 30, 30 }, { 0, 30, 30, 30 },       // 3, 4
    { 30, 30, 30, 30 }, { 60, 30, 30, 30 },     // 5, 6
    { 0, 60, 30, 30 }, { 30, 60, 30, 30 },      // 7, 8
    { 60, 60, 30, 30 }, { 90, 0, 30, 30 },      // 9, 10
    { 120, 0, 30, 30 }, { 150, 0, 30, 30 },     // 11, 12
    { 90, 30, 30, 30 }, { 90, 60, 30, 30 },    // 13, 14
    { 120, 60, 30, 30 }, { 90, 60, 30, 30 },   // 15, 16
    { 120, 60, 30, 30 }, { 150, 60, 30, 30 },      // 17, 18
    { 180, 0, 30, 30 }, { 180, 30, 30, 30 },     // 19, 20
    { 180, 90, 30, 30 }, { 210, 0, 30, 30 },    // 21, 22
    { 240, 0, 30, 30 }, { 270, 0, 30, 30 },   // 23, 24
    { 210, 30, 30, 30 }, { 240, 30, 30, 30 },     // 25, 26
    { 270, 30, 30, 30 }, { 210, 60, 30, 30 },   // 27, 28
    { 240, 60, 30, 30 }, { 270, 60, 30, 30 },   // 29, 30
    };

	struct Tile
	{
		int value;
		bool collider;
		Color color;
	};

	Tile* tiles;
	int tileCountX;
	int tileCountY;
	int tileSize;
    Vector2 position;

public:
	void Tilemap::Load(const char* valuesMap, const char* collidersMap);
    void Tilemap::Init(float scrW, float scrH, int tileSize);
	void Tilemap::Unload();
	void Tilemap::Draw(Texture2D tileset);
};

#endif