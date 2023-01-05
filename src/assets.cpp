#include "assets.h"

// Constructor
AssetManager::AssetManager(Manager *mManager) : manager(mManager) {}

// Destructor
AssetManager::~AssetManager() {
    for (const auto &tex : textures)
    {
        SDL_DestroyTexture(std::get<SDL_Texture *>(tex));
    }
}

// Adds texture to "textures"
void AssetManager::addTexture(const char *id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}