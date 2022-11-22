#include "tilemap.h"

// Constructor
Map::Map(){}

// Deconstructor
Map::~Map() {}

// Loads a map
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for(int x = 0; x < sizeX; x++) {
        for(int y = 0; y < sizeY; y++) {
            mapFile.get(tile);
            Game::addTile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore();
        }
    }

    mapFile.close();
}