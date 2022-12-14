#include "collision.h"

// Axis-Aligned Bounding Box Collision
bool Collision::AABB_r(const SDL_Rect &recA, const SDL_Rect &recB)
{
    // If recA and recB overlap, return true
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y)
    {
        return true;
    }

    return false;
}

void Collision::AABB(const Hitbox &hitA, const Hitbox &hitB)
{
    if (AABB_r(hitA.hitbox, hitB.hitbox))
        hitA.transform->velocity * -1;
}