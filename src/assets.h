#pragma once

/* Including */
#include "textures.h"
#include "vector.h"
#include "ECS/ECS.h"

#include <map>
#include <string>

// Asset Manager class
class AssetManager
{
private:
    // Map of textures
    std::map<std::string, SDL_Texture *> textures;

    Manager *manager;

public:
    // Constructors
    AssetManager(Manager *mManager);

    // Destructor
    ~AssetManager();

    // Adds texture to "textures"
    void addTexture(std::string id, const char *path);

    // Gets texture from "textures"
    SDL_Texture *getTexture(std::string id);
};