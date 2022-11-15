#include "tilemap.h"

// Temporary tilemap (check draw map method for further detail)
int lvl1[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 1, 3, 3, 1, 1, 0, 0 },
    { 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 3, 3, 3, 3, 1, 1, 1 },
    { 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1 },
    { 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3 }
};

// Constructor
Map::Map()
{
    dirt = TextureManager::LoadTexture("assets/textures/tiles/dirt.png");
    grass = TextureManager::LoadTexture("assets/textures/tiles/grass.png");
    path_grass = TextureManager::LoadTexture("assets/textures/tiles/path_grass.png");
    water = TextureManager::LoadTexture("assets/textures/tiles/water.png");

    LoadMap(lvl1);

    src.x = src.y = dest.x = dest.y = 0;
    src.w = src.h = dest.w = dest.h = 32;
}

// Deconstructor
Map::~Map() {
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(path_grass);
}

// Loads a map
void Map::LoadMap(int arr[20][25]) {
    for(int row = 0; row < 20; row++) {
        for(int column = 0; column < 25; column++) {
            map[row][column] = arr[row][column];
        }
    }
}

// Draws a map to the screen
void Map::DrawMap() {
    int type = 0;

    // For each element in a row / column
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 25; column++) {
            type = map[row][column];
            dest.x = column * 32;
            dest.y = row * 32;

            // Draws a texture based off value in array
            switch (type)
            {
                // 0 is for grass
                case 0:
                    TextureManager::Draw(grass, src, dest);
                    break;
                
                // 1 is for dirt
                case 1:
                    TextureManager::Draw(dirt, src, dest);
                    break;
                
                // 2 is for grass "paths"
                case 2:
                    TextureManager::Draw(path_grass, src, dest);
                    break;
                
                // 3 is for water
                case 3:
                    TextureManager::Draw(water, src, dest);
                    break;

                // Default
                default:
                    break;
            }
        }
    }
}