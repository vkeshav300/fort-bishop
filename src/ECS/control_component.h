#pragma once

// Including
#include "components.h"

class ControlComponent : public Component {
    private:
        TransformComponent *transform;
        SpriteComponent *sprite;

    public:
        // Constructors
        ControlComponent() = default;

        // Initializes component
        void init() override {
            transform = &parent->getComponent<TransformComponent>();
            sprite = &parent->getComponent<SpriteComponent>();
        }

        // Updates component
        void update() override {
            // Adjusts the velocity of the entity
            if(Game::event.type == SDL_KEYDOWN) {
                switch (Game::event.key.keysym.sym)
                {
                    // Going up
                    case SDLK_w:
                        transform->velocity.y = -1;
                        sprite->play("V");
                        break;

                    case SDLK_UP:
                        transform->velocity.y = -1;
                        sprite->play("V");
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = -1;
                        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                        sprite->play("H");
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = -1;
                        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                        sprite->play("H");
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 1;
                        sprite->play("V");
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 1;
                        sprite->play("V");
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 1;
                        sprite->play("R");
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 1;
                        sprite->play("R");
                        break;
                    
                    // Default
                    default:
                        break;
                }
            }

            // Stops entity
            if(Game::event.type == SDL_KEYUP)
            {
                switch (Game::event.key.keysym.sym)
                {
                    // Going up
                    case SDLK_w:
                        transform->velocity.y = 0;
                        sprite->play("I");
                        break;

                    case SDLK_UP:
                        transform->velocity.y = 0;
                        sprite->play("I");
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = 0;
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        sprite->play("I");
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = 0;
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        sprite->play("I");
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 0;
                        sprite->play("I");
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 0;
                        sprite->play("I");
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 0;
                        sprite->play("I");
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 0;
                        sprite->play("I");
                        break;
                    
                    // Default
                    default:
                        break;
                }
            }
        }
};