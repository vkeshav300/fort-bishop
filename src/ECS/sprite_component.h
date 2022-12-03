#pragma once

// Including
#include "components.h"
#include "../textures.h"
#include "../animation.h"
#include "../assets.h"

#include <map>
#include <string>

class SpriteComponent : public Component {
    private:
        // Sprite properties
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        // Animation properties
        bool animated = false;
        int frames = 0;
        int ms_delay = 100;

    public:
        int animIndex = 0;

        // Holds animations
        std::map<const char*, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        // Constructors
        SpriteComponent() = default;
        
        SpriteComponent(std::string id) {
            // Loading texture
            setTex(id);
        }

        SpriteComponent(std::string id, bool isAnimated) {
            // Loading texture
            setTex(id);

            // Sets animated to true
            animated = isAnimated;
        }

        // Destructor
        ~SpriteComponent() {
            SDL_DestroyTexture(texture);
        }

        // Wrapper for TextureManager::LoadTexture
        void setTex(std::string id) {
            texture = Game::assets->getTexture(id);
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

        void addAnim(int animType) {
            switch(animType) {
                case WALK_CYCLE: {
                    int move_speed = 250 * transform->move_factor;

                    // All walk cycle animations
                    Animation idle = Animation(0, 2, 750);
                    animations.emplace("I", idle);

                    Animation walk = Animation(1, 4, move_speed);
                    animations.emplace("H", walk);

                    Animation down = Animation(2, 2, move_speed);
                    animations.emplace("D", down);

                    Animation up = Animation(3, 2, move_speed);
                    animations.emplace("U", up);

                    play("I");

                    break;
                }
                
                case ITEM: {
                    // All item animations
                    Animation idle = Animation(0, 2, 750);
                    animations.emplace("I", idle);

                    Animation use = Animation(1, 4, 250);
                    animations.emplace("U", use);

                    play("I");

                    break;
                }
                
                default:
                    break;
            }
        }

        // Updates component
        void update() override {
            // If entity is animated, change selection from animation atlas
            if(animated) srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / ms_delay) % frames);

            // Gets the frame from the atlas (if there is one)
            srcRect.y = animIndex * transform->size.y;

            // Setting (x, y) of destination projection rect
            destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            destRect.w = transform->size.x * transform->scale;
            destRect.h = transform->size.y * transform->scale;
        }

        // Drawing texture to position of destRect
        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        // Plays specific animation
        void play(const char *animName) {
            animIndex = animations[animName].index;
            frames = animations[animName].frames;
            ms_delay = animations[animName].ms_delay;
        }
};