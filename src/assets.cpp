#include "assets.h"

AssetManager::AssetManager(Manager *mManager) : manager(mManager) {}

AssetManager::~AssetManager() {
    // Destroys all textures
    for (const auto &tex : textures)
    {
        SDL_DestroyTexture(std::get<SDL_Texture *>(tex));
    }

    // Closes all fonts
    for (const auto &font : fonts)
    {
        TTF_CloseFont(std::get<TTF_Font *>(font));
    }
}

void AssetManager::addTexture(const char *id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

void AssetManager::addFont(const char *id, const char *path, int size)
{
    fonts.emplace(id, TTF_OpenFont(path, size));
}

void AssetManager::addColor(const char *id, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b};
    colors.emplace(id, &color);
}