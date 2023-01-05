#pragma once

#include "components.h"
#include "../textures.h"
#include "../assets.h"
#include "../custom_types/vector.h"

class TileComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    Vector2D position;

    // Constructors
    TileComponent() = default;

    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char *id) : texture(Game::assets->textures[id])
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
    ~TileComponent()
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