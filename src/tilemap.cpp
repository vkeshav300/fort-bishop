#include "tilemap.h"

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

    for(int x = 0; x < sizeX; x++) {
        for(int y = 0; y < sizeY; y++) {
            mapFile.get(c);
            srcY = atoi(&c) * 32;
            mapFile.get(c);
            srcX = atoi(&c) * 32;
            Game::addTile(srcX, srcY, x * 32, y * 32);
            mapFile.ignore();
        }
    }

    mapFile.close();
}