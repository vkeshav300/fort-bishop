#include "ecs_base.h"

// Adds group to entity and adds entity to group
void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.addToGroup(this, mGroup);
}