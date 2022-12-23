#pragma once

// Including
#include "components.h"

/*
NOTE:
This component uses an enum direction system
found in game.h
*/

class ControlComponent : public Component {
    private:
        TransformComponent *transform;
        SpriteComponent *sprite;

        // Current directions in (x, y) axis
        int currentxdir = IDLE;
        int currentydir = IDLE;

    public:
        // Constructors
        ControlComponent() = default;

        // Initializes component
        void init() override {
            transform = &parent->getComponent<TransformComponent>();
            sprite = &parent->getComponent<SpriteComponent>();
        }

        void playAnimFromEnumDirections() {
            switch(currentydir) {
                case IDLE:
                    sprite->spriteFlip = SDL_FLIP_NONE;

                    switch(currentxdir) {
                        // Full IDLE
                        case IDLE:
                            sprite->play("I");
                            break;

                        // Full LEFT
                        case LEFT:
                            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                            sprite->play("walk");
                            break;
                            
                        // Full RIGHT
                        case RIGHT:
                            sprite->play("walk");
                            break;

                        default:
                            break;
                    }

                    break;

                case UP:
                    sprite->spriteFlip = SDL_FLIP_NONE;

                    switch(currentxdir) {
                        // Full UP
                        case IDLE:
                            sprite->play("U");
                            break;

                        // UPLEFT
                        case LEFT:
                            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                            sprite->play("walk");
                            break;
                            
                        // UPRIGHT
                        case RIGHT:
                            sprite->play("walk");
                            break;

                        default:
                            break;
                    }

                    break;
            
                case DOWN:
                    sprite->spriteFlip = SDL_FLIP_NONE;

                    switch(currentxdir) {
                        // Full DOWN
                        case IDLE:
                            sprite->play("D");
                            break;

                        // DOWNLEFT
                        case LEFT:
                            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                            sprite->play("walk");
                            break;
                            
                        // DOWNRIGHT
                        case RIGHT:
                            sprite->play("walk");
                            break;

                        default:
                            break;
                    }

                    break;

                default:
                    break;
            }
        }

        // Updates component
        void update() override {
            // Adjusts the velocity of the entity
            if(Game::event.type == SDL_KEYDOWN) {
                switch (Game::event.key.keysym.sym) {
                    // Going up
                    case SDLK_w:
                        transform->velocity.y = -1;
                        currentydir = UP;
                        break;

                    case SDLK_UP:
                        transform->velocity.y = -1;
                        currentydir = UP;
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = -1;
                        currentxdir = LEFT;
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = -1;
                        currentxdir = LEFT;
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 1;
                        currentydir = DOWN;
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 1;
                        currentydir = DOWN;
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 1;
                        currentxdir = RIGHT;
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 1;
                        currentxdir = RIGHT;
                        break;
                    
                    // Default
                    default:
                        break;
                }
            }

            // Stops entity
            if(Game::event.type == SDL_KEYUP) {
                switch (Game::event.key.keysym.sym) {
                    // Going up
                    case SDLK_w:
                        transform->velocity.y = 0;
                        currentydir = IDLE;
                        break;

                    case SDLK_UP:
                        transform->velocity.y = 0;
                        currentydir = IDLE;
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = 0;
                        currentxdir = IDLE;
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = 0;
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        currentxdir = IDLE;
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 0;
                        currentydir = IDLE;
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 0;
                        currentydir = IDLE;
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 0;
                        currentxdir = IDLE;
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 0;
                        currentxdir = IDLE;
                        break;
                    
                    // Default
                    default:
                        break;
                }
            }

            playAnimFromEnumDirections();
        }
};