#pragma once

/* Including */
#include "textures.h"
#include "custom_types/vector.h"
#include "ECS/ECS.h"

#include <map>

// Asset Manager class
class AssetManager
{
private:
    Manager *manager;

public:
    // Map of textures
    std::map<const char *, SDL_Texture *> textures;
    
    // Constructors
    AssetManager(Manager *mManager);

    // Destructor
    ~AssetManager();

    // Adds texture to "textures"
    void addTexture(const char *id, const char *path);

    // Gets texture from "textures"
    SDL_Texture *getTexture(const char *id);
};