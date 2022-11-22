#pragma once

// Including
#include "components.h"
#include <string>

class HitboxComponent : public Component {
    private:
        TransformComponent *transform;

    public:
        SDL_Rect hitbox;
        std::string tag;

        // Constructors
        HitboxComponent() = default;

        HitboxComponent(std::string t) {tag = t;}

        // Initializes component
        void init() override {
            // If entity does not have a "TransformComponent", it will automatically add one to prevent errors  
            if(!parent->hasComponent<TransformComponent>()) {parent->addComponent<TransformComponent>();}

            transform = &parent->getComponent<TransformComponent>();
        }

        // Updates component
        void update() override {
            // Updates hitbox
            hitbox.x = static_cast<int>(transform->position.x);
            hitbox.y = static_cast<int>(transform->position.y);
            hitbox.w = transform->size.x * transform->scale;
            hitbox.h = transform->size.y * transform->scale;
        }
};