#pragma once

#include "components.h"
#include "../textures.h"
#include "../assets.h"
#include "../custom_types/vector.h"

class Tile : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    vector position;

    // Constructors
    Tile() = default;

    Tile(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char *id) : texture(Game::assets->textures[id])
    {
        // Sets position
        position.x = xpos;
        position.y = ypos;

        // Setting up srcRect
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;

        // Setting up destRect
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    // Destructor
    ~Tile()
    {
        SDL_DestroyTexture(texture);
    }

    void update() override
    {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};