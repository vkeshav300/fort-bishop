#pragma once

/* Including */
#include "SDL2_ttf/SDL_ttf.h"

#include "textures.h"
#include "custom_types/vector.h"
#include "ECS/ecs_base.h"

#include <map>

// Asset Manager class
class AssetManager
{
private:
    Manager *manager;

public:
    // Map of textures
    std::map<const char *, SDL_Texture *> textures;

    // Map of fonts
    std::map<const char *, TTF_Font *> fonts;

    // Map of colors
    std::map<const char *, SDL_Color *> colors;

    AssetManager(Manager *mManager);

    ~AssetManager();

    void addTexture(const char *id, const char *path);

    void addFont(const char *id, const char *path, int size);

    void addColor(const char *id, Uint8 r, Uint8 g, Uint8 b);
};