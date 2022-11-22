// Comments found in "collision.cpp"
#pragma once

#include "game.h"
#include "ECS/components.h"

class Collision {
    public:
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
        static bool AABB(const HitboxComponent& hitA, const HitboxComponent& hitB);
};