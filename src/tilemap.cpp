#include "tilemap.h"

void Tilemap::Load(const char* valuesMap, const char* collidersMap) {
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

            tiles = (Tile*)malloc(counter * sizeof(Tile));

            tileCountX = 27;
            tileCountY = 23;
            counter = 0;

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &tiles[counter].value);
                counter++;
            }

            fclose(valuesFile);

            // Read values from text file
            // NOTE: Colliders map data MUST match values data, 
            // or we need to do a previous check like done with values data
            FILE* collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(collidersFile))
            {
                fscanf(collidersFile, "%i", &temp);
                tiles[counter].collider = temp;

                counter++;
            }

            fclose(collidersFile);

#if DEBUG   // print tilemap information loaded
            for (int j = 0; j < tileCountY; j++)
            {
                for (int i = 0; i < tileCountX; i++)
                {
                    printf("%i ", tiles[j * tileCountX + i].collider);
                }
                printf("\n");
            }
#endif
        }
    }
}

void Tilemap::Init(float scrW, float scrH, int tileSize) 
{
    this->tileSize = tileSize;
    position = {
        scrW / 2 - tileCountX * tileSize / 2,
        scrH / 2 - tileCountY * tileSize / 2
    };
}

void Tilemap::Unload() 
{
    if (tiles != NULL) free(tiles);
}

void Tilemap::Draw(Texture2D tileset) 
{
    for (int y = 0; y < tileCountY; y++)
    {
        for (int x = 0; x < tileCountX; x++)
        {
            // Draw each piece of the tileset in the right position to build map
            DrawTextureRec(tileset, tilesetRecs[tiles[y * tileCountX + x].value - 1], Vector2 {position.x + x * tileSize, position.y + y * tileSize}, WHITE);
        }
    }
}