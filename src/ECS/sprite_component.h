#pragma once

// Including
#include "components.h"
#include "../vector.h"
#include "../textures.h"

class SpriteComponent : public Component {
    private:
        // Initializing variables
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;
    
    public:
        // Constructors
        SpriteComponent() {}

        SpriteComponent(const char *path) {
            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 32;
            destRect.w = destRect.h = srcRect.w * 2;

            texture = TextureManager::LoadTexture(path);
        }

        SpriteComponent(const char *path, int w, int h) {
            srcRect.w = w; srcRect.h = h;
            destRect.w = srcRect.w * 2; destRect.h = srcRect.h * 2;
        }

        // Init method (gets transform component)
        void init() override {
            transform = &parent->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
        }

        // Draws textures to transform->position(x, y)
        void update() override {
            destRect.x = transform->position.x;
            destRect.y = transform->position.y;

            TextureManager::Draw(texture, srcRect, destRect);
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};