// Comments found in "collision.cpp"
#pragma once

#include "game.h"

class Collision {
    public:
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};