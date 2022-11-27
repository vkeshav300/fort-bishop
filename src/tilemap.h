// Comments found in "tilemap.cpp"
#pragma once

#include "game.h"
#include "textures.h"

#include <string>

class Map {
    public:
        Map();
        ~Map();

        static void LoadMap(std::string path, int sizeX, int sizeY);
};