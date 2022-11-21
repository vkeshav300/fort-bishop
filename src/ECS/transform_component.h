#pragma once

// Including
#include "components.h"
#include "../vector.h"

class TransformComponent: public Component {
    public:
        // Vectors (x, y) for position and velocity
        Vector2D position;
        Vector2D velocity = Vector2D(0.0f, 0.0f); // By default velocity will be set to (0, 0)

        // Vector (x, y) for size (width, height)
        Vector2D size = Vector2D(32.0f, 32.0f);

        // Scale factor
        int scale = 1.0f;

        /*
        "move_factor" determines how many pixels / second an entity will move (position.(x,y) = velocity.(x,y) * move_factor)
        if a player were to drink a potion to adjust their speed, move factor would be adjusted, not velocity.
        */
        float move_factor = 1.0f;

        // Constructors
        // By default position will be at (0, 0)
        TransformComponent() {position.x = position.y = 0.0f;}
        
        TransformComponent(float xPos, float yPos) {
            position.x = xPos;
            position.y = yPos;
        }

        TransformComponent(float xPos, float yPos, int w, int h) {
            position.x = xPos;
            position.y = yPos;
            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);
        }

        TransformComponent(float xPos, float yPos, int w, int h, int SF) {
            position.x = xPos;
            position.y = yPos;
            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);
            scale = SF;
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