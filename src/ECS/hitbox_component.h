#pragma once

// Including
#include "components.h"

class Hitbox : public Component
{
public:
    Transform *transform;
    SDL_Rect hitbox;
    const char *tag;

    // Constructors
    Hitbox() = default;

    Hitbox(const char *t) : tag(t) {}

    // Initializes component
    void init() override
    {
        // If entity does not have a "Transform", it will automatically add one to prevent errors
        if (!parent->hasComponent<Transform>())
        {
            parent->addComponent<Transform>();
        }

        transform = &parent->getComponent<Transform>();

        Game::collisions.push_back(this);
    }

    // Updates component
    void update() override
    {
        // Updates hitbox
        hitbox.x = static_cast<int>(transform->position.x);
        hitbox.y = static_cast<int>(transform->position.y);
        hitbox.w = transform->size.x * transform->scale;
        hitbox.h = transform->size.y * transform->scale;
    }
};