#include "collision.h"

// Axis-Aligned Bounding Box Collision
bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB) {
    // If recA and recB overlap, return true
    if(
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    ) {
        return true;
    }

    return false;
}

bool Collision::AABB(const HitboxComponent& hitA, const HitboxComponent& hitB) {
    if (AABB(hitA.hitbox, hitB.hitbox)) return true;
	
    return false;
}