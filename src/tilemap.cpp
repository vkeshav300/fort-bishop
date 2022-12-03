// Including
#include "tilemap.h"
#include "game.h"
#include "assets.h"

#include <fstream>
#include <cstdlib>

// Constructor
Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) {
	scaledSize = ms * ts;
}

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
            srcY = atoi(&c) * tileSize;

            mapFile.get(c);
            srcX = atoi(&c) * tileSize;

            // Adds tile
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(Game::manager->addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(groupMap);
}