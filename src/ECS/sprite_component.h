#pragma once

// Including
#include "components.h"

class SpriteComponent : public Component {
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        // Constructors
        SpriteComponent() = default;
        
        SpriteComponent(const char *path) {
            // Loading texture
            texture = TextureManager::LoadTexture(path);

            // Setting height and position of projection rects
            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 32;
            destRect.w = destRect.h = srcRect.w * 2;
        }

        SpriteComponent(const char *path, int width, int height) {
            // Loading texture
            texture = TextureManager::LoadTexture(path);

            // Setting height and position of projection rects
            srcRect.x = srcRect.y = 0;
            srcRect.w = width;
            srcRect.h = height;
            destRect.w = width * 2;
            destRect.h = height * 2;
        }

        // Initializes component
        void init() override {
            // Getting transform component via entity->getComponent function
            transform = &parent->getComponent<TransformComponent>();
        }

        // Updates component
        void update() override {
            // Setting (x, y) of destRect projection rect
            destRect.x = transform->position.x;
            destRect.y = transform->position.y;
        }

        // Drawing texture to position of destRect
        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};