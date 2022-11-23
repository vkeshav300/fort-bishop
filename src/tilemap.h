// Comments found in "tilemap.cpp"
#pragma once

#include "game.h"
#include "textures.h"

#include <string>
#include <fstream>
#include <cstdlib>

class Map {
    public:
        Map();
        ~Map();

        static void LoadMap(std::string path, int sizeX, int sizeY);
};