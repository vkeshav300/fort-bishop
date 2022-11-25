#pragma once

#include "components.h"

class TileComponent : public Component {
    public:
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        // Constructors
        TileComponent() = default;

        TileComponent(int srcX, int srcY, int xpos, int ypos, const char *path) {
            // Loads texture
            texture = TextureManager::LoadTexture(path);

            // Setting up srcRect
            srcRect.x = srcX;
            srcRect.y = srcY;
            srcRect.w = srcRect.h = 32;

            // Setting up destRect
            destRect.x = xpos;
            destRect.y = ypos;
            destRect.w = destRect.h = 32;
        }

        // Destructor
        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        }
};