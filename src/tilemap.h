// Comments found in "tilemap.cpp"
#pragma once

#include "SDL2/SDL.h"
#include "textures.h"

#include <string>

class Map {
    private:
        std::string texID;
	    int mapScale;
	    int tileSize;
	    int scaledSize;

    public:
        Map(std::string tID, int ms, int ts);
        ~Map();

        void LoadMap(std::string path, int sizeX, int sizeY);
        void addTile(int srcX, int srcY, int xpos, int ypos);
};