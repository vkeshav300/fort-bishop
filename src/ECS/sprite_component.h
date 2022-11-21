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
            srcRect.w = static_cast<int>(transform->size.x);
            srcRect.h = static_cast<int>(transform->size.y);
            destRect.w = static_cast<int>(transform->size.x * transform->scale);
            destRect.h = static_cast<int>(transform->size.y * transform->scale);
        }

        // Updates component
        void update() override {
            // Setting (x, y) of destRect projection rect
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
        }

        // Drawing texture to position of destRect
        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};