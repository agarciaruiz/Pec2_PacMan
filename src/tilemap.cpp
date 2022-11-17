#include "tilemap.h"


Rectangle Tilemap::GetBounds(int x, int y) const 
{
    return Rectangle{ _position.x + x * _tileSize, _position.y + y * _tileSize, (float)_tileSize, (float)_tileSize};
}
Vector2 Tilemap::Position() const { return _position; }
int Tilemap::TileSize() const { return _tileSize; }
int Tilemap::TileCountX() const { return _tileCountX; }
int Tilemap::TileCountY() const { return _tileCountY; }
Tilemap::Tile* Tilemap::Tiles() const { return _tiles; }

void Tilemap::Load(const char* valuesMap, const char* collidersMap, const char* objectsMap) {
    const char* fileExt;

    if ((fileExt = strrchr(valuesMap, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0)
        {
            int counter = 0;
            int temp = 0;

            // Read values from text file
            FILE* valuesFile = fopen(valuesMap, "rt");

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &temp);
                counter++;
            }

            rewind(valuesFile);        // Return to the beginning of the file, to read again

            _tiles = (Tile*)malloc(counter * sizeof(Tile));

            _tileCountX = 27;
            _tileCountY = 23;
            counter = 0;

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &_tiles[counter].value);
                counter++;
            }

            fclose(valuesFile);

            // Read values from object file
            FILE* objectsFile = fopen(objectsMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(objectsFile))
            {
                fscanf(objectsFile, "%i", &temp);
                _tiles[counter].object = temp;
                counter++;
            }
            numOfPills = counter;
            fclose(objectsFile);

            // Read values from text file
            // NOTE: Colliders map data MUST match values data, 
            // or we need to do a previous check like done with values data
            FILE* collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(collidersFile))
            {
                fscanf(collidersFile, "%i", &temp);
                _tiles[counter].collider = temp;

                counter++;
            }

            fclose(collidersFile);
        }
    }
}

void Tilemap::Init(float scrW, float scrH, int tileSize) 
{
    this->_tileSize = tileSize;
    _position = {
        scrW / 2 - _tileCountX * tileSize / 2,
        scrH / 2 - _tileCountY * tileSize / 2
    };
}

void Tilemap::Unload() 
{
    if (_tiles != NULL) free(_tiles);
}

void Tilemap::Draw(Texture2D tileset) 
{
    for (int y = 0; y < _tileCountY; y++)
    {
        for (int x = 0; x < _tileCountX; x++)
        {
            // Draw each piece of the tileset in the right position to build map
            DrawTextureRec(tileset, tilesetRecs[_tiles[y * _tileCountX + x].value - 1], Vector2 { _position.x + x * _tileSize, _position.y + y * _tileSize }, WHITE);
            DrawTextureRec(tileset, tilesetRecs[_tiles[y * _tileCountX + x].object - 1], Vector2{ _position.x + x * _tileSize, _position.y + y * _tileSize }, WHITE);
        }
    }
}