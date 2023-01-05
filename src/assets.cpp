#include "assets.h"

// Constructor
AssetManager::AssetManager(Manager *mManager) : manager(mManager) {}

// Destructor
AssetManager::~AssetManager() {}

// Parsing and writing data
void AssetManager::loadData(const char *path)
{

}

void AssetManager::saveData(const char *path)
{
}

// Adds texture to "textures"
void AssetManager::addTexture(const char *id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

// Gets texture from "textures"
SDL_Texture *AssetManager::getTexture(const char *id)
{
    return textures[id];
}