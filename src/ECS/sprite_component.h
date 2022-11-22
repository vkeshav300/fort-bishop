#pragma once

// Including
#include "components.h"
#include "../assets.h"

class SpriteComponent : public Component {
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int ms_delay = 100;

    public:
        // Constructors
        SpriteComponent() = default;
        
        SpriteComponent(const char *path) {
            // Loading texture
            setTex(path);
        }

        SpriteComponent(const char *path, int nFrames, int mDelay) {
            // Loading texture
            setTex(path);

            // Animation properties
            animated = true;
            frames = nFrames;
            ms_delay = mDelay;
        }

        // Deconstructors
        ~SpriteComponent() {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char *path) {
            texture = TextureManager::LoadTexture(path);
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
            // If entity is animated, change selection from animation atlas
            if(animated) srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / ms_delay) % frames);

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