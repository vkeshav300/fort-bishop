// Comments found in "tilemap.cpp"
#pragma once

#include "SDL2/SDL.h"
#include "textures.h"

class Map
{
private:
    const char *texID;
    int mapScale;
    int tileSize;
    int scaledSize;

public:
    Map(const char *tID, int ms, int ts);
    ~Map();

    void LoadMap(const char *path, int sizeX, int sizeY);
    void addTile(int srcX, int srcY, int xpos, int ypos);
};