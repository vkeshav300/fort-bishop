#pragma once

// Including
#include "components.h"
#include "../assets.h"

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
        }

        // Deconstructors
        ~SpriteComponent() {
            SDL_DestroyTexture(texture);
        }

        // Initializes component
        void init() override {
            // If entity does not have a "TransformComponent", it will automatically add one to prevent errors  
            if(!parent->hasComponent<TransformComponent>()) {parent->addComponent<TransformComponent>();}

            transform = &parent->getComponent<TransformComponent>();

            // Setting height and position of projection rects
            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->size.x;
            srcRect.h = transform->size.y;
        }

        // Updates component
        void update() override {
            // Setting (x, y) of destination projection rect
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = transform->size.x * transform->scale;
            destRect.h = transform->size.y * transform->scale;
        }

        // Drawing texture to position of destRect
        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};