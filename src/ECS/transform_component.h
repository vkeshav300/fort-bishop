#pragma once

// Including
#include "components.h"
#include "../vector.h"

class TransformComponent: public Component {
    public:
        // Vectors (x, y) for position and velocity
        Vector2D position;
        Vector2D velocity = Vector2D(0.0f, 0.0f); // By default velocity will be set to (0, 0)

        /*
        "move_factor" determines how many pixels / second an entity will move (position.(x,y) = velocity.(x,y) * move_factor)
        if a player were to drink a potion to adjust their speed, move factor would be adjusted, not velocity.
        */
        int move_factor = 1;

        // Constructors
        // By default position will be at (0, 0)
        TransformComponent() {position.x = position.y = 0.0f;}
        
        TransformComponent(float xPos, float yPos) {
            position.x = xPos;
            position.y = yPos;
        }

        // Initializes component
        void init() override {
            velocity.x = 0;
            velocity.y = 0;
        }

        // Adds the velocity to the position every frame (to move the entity)
        void update() override {
            velocity.x = velocity.x * move_factor;
            velocity.y = velocity.y * move_factor;

            position.add(velocity);
        }

        // Forces the entity to move to a specific location without factoring in "velocity" or "move_factor"
        void forceMove(int xPos, int yPos) {
            position.x = xPos;
            position.y = yPos;
        }
};