#pragma once

// Including
#include "components.h"
#include "../vector.h"

class TransformComponent: public Component {
    public:
        // Vectors (x, y) for position and velocity
        Vector2D position; // By default position will be set to (0, 0)
        Vector2D velocity; // By default velocity will be set to (0, 0)

        /*
        "move_factor" determines how many pixels / second an entity will move (position.(x,y) = velocity.(x,y) * move_factor)
        if a player were to drink a potion to adjust their speed, move factor would be adjusted, not velocity.
        By default "move_factor" will be set to 1.
        */
        float move_factor = 1.0f;

        // Vector (x, y) for size (width, height)
        Vector2D size = Vector2D(32.0f, 64.0f); // By default size will be set to (0, 0)

        // Scale factor
        int scale = 1; // By default scale will be set to 1

        // Health
        bool invincible = false; // By default invincible will be set to false

        // Vector (current_health, max_health) for health.
        Vector2D health = Vector2D(10.0f, 10.0f); // By default health will be set to 10/10

        // Constructors
        TransformComponent() {
            position.Zero();
        }

        TransformComponent(int SF) : scale(SF) {
            position.Zero();
        }

        TransformComponent(int SF, bool ndmg, int maxHealth) : scale(SF), invincible(ndmg) {
            health.x = health.y = maxHealth;
            
            position.Zero();
        }
        
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

        TransformComponent(float xPos, float yPos, int w, int h, bool ndmg, int maxHealth) : invincible(ndmg) {
            // Position and size vectors
            position.x = xPos;
            position.y = yPos;
            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);

            // Health
            health.x = health.y = maxHealth;
        }

        TransformComponent(float xPos, float yPos, int w, int h, int SF) : scale(SF) {
            position.x = xPos;
            position.y = yPos;
            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);
        }

        TransformComponent(float xPos, float yPos, int w, int h, bool ndmg, int maxHealth, int SF) : scale(SF), invincible(ndmg) {
            // Position and size vectors
            position.x = xPos;
            position.y = yPos;
            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);

            // Health
            health.x = health.y = maxHealth;
        }

        // Initializes component
        void init() override {
            if(invincible) health.x = health.y = 1;

            velocity.Zero();
        }

        // Adds the velocity to the position every frame (to move the entity)
        void update() override {
            position.x += velocity.x * move_factor;
            position.y += velocity.y * move_factor;
        }

        // Forces the entity to move to a specific location without factoring in "velocity" or "move_factor"
        void forceMove(int xPos, int yPos) {
            position.x = xPos;
            position.y = yPos;
        }

        // Damages entity (with accordance to invicible boolean)
        void damage(int amt) {
            if(invincible || health.x <= 0) return;

            // Subtracts health from entity
            health.x -= amt;

            if(health.x <= 0) health.x = 0;
        }

        // Heals the entity (with accordance to invincible boolean)
        void heal(int amt) {
            if(invincible) return;

            health.x += amt;

            if(health.x > health.y) health.x = health.y;
        }
};