// Including
#include "tilemap.h"

#include <fstream>
#include <cstdlib>

// Constructor
Map::Map(){}

// Deconstructor
Map::~Map() {}

// Loads a map
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;
    
    // For (row, column)
    for(int x = 0; x < sizeX; x++) {
        for(int y = 0; y < sizeY; y++) {
            // Gets srcX and srcY from mapFile via cstdlib atoi function
            mapFile.get(c);
            srcY = atoi(&c) * 32;

            mapFile.get(c);
            srcX = atoi(&c) * 32;

            // Adds tile
            Game::addTile(srcX, srcY, x * 32, y * 32);
            mapFile.ignore();
        }
    }

    mapFile.close();
}