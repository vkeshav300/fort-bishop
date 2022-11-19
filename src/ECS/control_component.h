#pragma once

// Including
#include "components.h"

class ControlComponent : public Component {
    private:
        TransformComponent *transform;

    public:
        ControlComponent() = default;

        void init() override {
            transform = &parent->getComponent<TransformComponent>();
        }

        void update() override {
            // Adjusts the velocity of the entity
            if(Game::event.type == SDL_KEYDOWN) {
                switch (Game::event.key.keysym.sym)
                {
                    // Going up
                    case SDLK_w:
                        transform->velocity.y = -1;
                        break;

                    case SDLK_UP:
                        transform->velocity.y = -1;
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = -1;
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = -1;
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 1;
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 1;
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 1;
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 1;
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
                        break;

                    case SDLK_UP:
                        transform->velocity.y = 0;
                        break;

                    // Going left
                    case SDLK_a:
                        transform->velocity.x = 0;
                        break;

                    case SDLK_LEFT:
                        transform->velocity.x = 0;
                        break;

                    // Going down
                    case SDLK_s:
                        transform->velocity.y = 0;
                        break;

                    case SDLK_DOWN:
                        transform->velocity.y = 0;
                        break;

                    // Going right
                    case SDLK_d:
                        transform->velocity.x = 0;
                        break;
                    
                    case SDLK_RIGHT:
                        transform->velocity.x = 0;
                        break;
                    
                    // Default
                    default:
                        break;
                }
            }
        }
};