#pragma once

// Including
#include "components.h"
#include "../custom_types/vector.h"

class Transform : public Component
{
public:
    // * Vectors (x, y) for position velocity, and size
    vector position = vector(0.0f, 0.0f);
    vector velocity = vector(0.0f, 0.0f); 
    vector size = vector(32.0f, 64.0f); 
    vector health = vector(10.0f, 10.0f);

    int scale = 1;

    /*
    ? "move_factor" determines how many pixels / second an entity will move (position.(x,y) = velocity.(x,y) * move_factor)
    ? if a player were to drink a potion to adjust their speed, move factor would be adjusted, not velocity.
    */
    float move_factor = 1.0f;

    bool invincible = false;
    
    Transform() = default;

    Transform(int SF) : scale(SF) {}

    Transform(int SF, bool ndmg, int maxHealth) : scale(SF), invincible(ndmg)
    {
        health.x = health.y = maxHealth;
    }

    Transform(float xPos, float yPos)
    {
        position.x = xPos;
        position.y = yPos;
    }

    Transform(float xPos, float yPos, int w, int h)
    {
        position.x = xPos;
        position.y = yPos;
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);
    }

    Transform(float xPos, float yPos, int w, int h, bool ndmg, int maxHealth) : invincible(ndmg)
    {
        // Position and size vectors
        position.x = xPos;
        position.y = yPos;
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);

        // Health
        health.x = health.y = maxHealth;
    }

    Transform(float xPos, float yPos, int w, int h, int SF) : scale(SF)
    {
        position.x = xPos;
        position.y = yPos;
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);
    }

    Transform(float xPos, float yPos, int w, int h, bool ndmg, int maxHealth, int SF) : scale(SF), invincible(ndmg)
    {
        // Position and size vectors
        position.x = xPos;
        position.y = yPos;
        size.x = static_cast<float>(w);
        size.y = static_cast<float>(h);

        // Health
        health.x = health.y = maxHealth;
    }
    void init() override
    {
        if (invincible)
            health.x = health.y = 1;

        velocity.Zero();
    }

    void update() override
    {
        /*
        ? Moves the player by adding velocity * move_factor each frame
        ? The equation is: Pos = V * Mfactor
        */
        position.x += velocity.x * move_factor;
        position.y += velocity.y * move_factor;
    }

    // ? Forces the entity to move to a specific location without factoring in velocity or move_factor
    void forceMove(int xPos, int yPos)
    {
        position.x = xPos;
        position.y = yPos;
    }

    void damage(int amt)
    {
        if (invincible || health.x <= 0)
            return;

        // Subtracts health from entity
        health.x -= amt;

        if (health.x <= 0)
            health.x = 0;
    }

    void heal(int amt)
    {
        if (invincible)
            return;

        health.x += amt;

        if (health.x > health.y)
            health.x = health.y;
    }
};