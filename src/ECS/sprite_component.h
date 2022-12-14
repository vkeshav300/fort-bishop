#pragma once

// Including
#include "components.h"
#include "../textures.h"
#include "../custom_types/animation.h"
#include "../assets.h"

#include <map>

class Sprite : public Component
{
private:
    // Sprite properties
    Transform *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool camera_interact = true;

    // Animation properties
    bool animated = false;
    int frames = 0;
    int ms_delay = 100;

public:
    int animIndex = 0;

    // Holds animations
    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    Sprite() = default;

    Sprite(const char *id)
    {
        setTex(id);
    }

    Sprite(bool cam_interact, const char *id) : camera_interact(cam_interact)
    {
        setTex(id);
    }

    Sprite(const char *id, bool isAnimated) : animated(isAnimated)
    {
        setTex(id);
    }

    Sprite(const char *id, bool isAnimated, bool cam_interact) : animated(isAnimated), camera_interact(cam_interact)
    {
        setTex(id);
    }

    ~Sprite()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char *id)
    {
        texture = Game::assets->textures[id];
    }

    void addAnim(int animType)
    {
        switch (animType)
        {
        case WALK_CYCLE:
        {
            int move_speed = 250 * transform->move_factor;

            // All walk cycle animations
            Animation idle = Animation(0, 2, 750);
            animations.emplace("I", idle);

            Animation walk = Animation(1, 4, move_speed);
            animations.emplace("H", walk);

            Animation down = Animation(2, 2, move_speed);
            animations.emplace("D", down);

            Animation up = Animation(3, 2, move_speed);
            animations.emplace("U", up);

            play("I");

            break;
        }

        case ITEM:
        {
            // All item animations
            Animation idle = Animation(0, 2, 750);
            animations.emplace("I", idle);

            Animation use = Animation(1, 4, 250);
            animations.emplace("U", use);

            play("I");

            break;
        }

        default:
            break;
        }
    }

    void init() override
    {
        // If entity does not have a "TransformComponent", it will automatically add one to prevent errors
        if (!parent->hasComponent<Transform>())
        {
            parent->addComponent<Transform>();
        }

        transform = &parent->getComponent<Transform>();

        // Setting height and position of projection rects
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->size.x;
        srcRect.h = transform->size.y;
    }

    void update() override
    {
        // If entity is animated, change selection from animation atlas
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / ms_delay) % frames);
        }

        // Gets the frame from the atlas (if there is one)
        srcRect.y = animIndex * transform->size.y;

        // Setting (x, y) of destination projection rect
        if (camera_interact)
        {
            destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
            destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
        }
        else
        {
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
        }

        destRect.w = transform->size.x * transform->scale;
        destRect.h = transform->size.y * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    // Plays specified animation
    void play(const char *animName)
    {
        animIndex = animations[animName].index;
        frames = animations[animName].frames;
        ms_delay = animations[animName].ms_delay;
    }
};