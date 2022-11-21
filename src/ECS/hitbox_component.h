#pragma once

// Including
#include "components.h"
#include <string>

class HitboxComponent : public Component {
    private:
        TransformComponent *transform;

        SDL_Rect collider;
        std::string tag;

    public:
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
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->size.x * transform->scale;
            collider.h = transform->size.y * transform->scale;
        }
};