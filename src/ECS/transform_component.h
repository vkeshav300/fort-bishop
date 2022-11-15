#pragma once

// Including
#include "components.h"
#include "../vector.h"

class TransformComponent: public Component {
    public:
        // Vectors (x, y) for position and velocity
        Vector2D position;
        Vector2D velocity = Vector2D(0.0f, 0.0f); // By default velocity will be set to (0, 0)

        // "move_factor" determines how many pixels / second an entity will move ("velocity.x = <direction as an int> * move_factor")
        int move_factor = 3;

        // By default position will be at (0, 0)
        TransformComponent() {position.x = position.y = 0.0f;}
        
        TransformComponent(int xPos, int yPos) {
            position.x = static_cast<float>(xPos);
            position.y = static_cast<float>(yPos);
        }

        // Adds the velocity to the position every frame (to move the entity)
        void update() override {
            position.add(velocity);
        }

        // Forces the entity to move to a specific location without factoring in "velocity" or "move_factor"
        void ForceMove(int xPos, int yPos) {
            position.x = static_cast<int>(xPos);
            position.y = static_cast<int>(yPos);
        }
};