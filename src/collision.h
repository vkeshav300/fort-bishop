// Comments found in "collision.cpp"
#pragma once

#include "SDL2/SDL.h"
#include "ECS/components.h"

class Collision {
    public:
        static bool AABB_r(const SDL_Rect& recA, const SDL_Rect& recB);
        static void AABB(const HitboxComponent& hitA, const HitboxComponent& hitB);
};