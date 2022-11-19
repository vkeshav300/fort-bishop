#pragma once

#include <typeinfo>
#include <array>
#include <bitset>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

// Forward declaration of entity and component
class Entity;
class Component;

// Getting component methods and setting up ECS
using ComponentTypeId = std::size_t;

inline ComponentTypeId getUniqueComponentID() {
    static ComponentTypeId lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentTypeId getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "Failed at getComponentTypeID/static_assert() --> ECS/ECS.h");
    static const ComponentTypeId typeID = getUniqueComponentID();
    return typeID;
}

constexpr std::size_t MAX_ENTITIES = 5000;
constexpr std::size_t MAX_COMPONENTS = 30;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

// Base "Component" class
class Component {
    public:
        Entity* parent;

        Component() = default;
        virtual ~Component() = default;

        virtual void init() {}

        virtual void draw() {}

        virtual void update() {}
};

// Base "Entity" class
class Entity {
    private:
        ComponentArray compArr;
        ComponentBitset compBitset;
        std::vector<std::unique_ptr<Component>> components;

        bool active = true;

    public:
        Entity() {}
        virtual ~Entity() {}

        template<typename T, typename... TArgs> T& addComponent(TArgs&&... args) {
            // Create Component
            T* c(new T(std::forward<TArgs>(args)...));

            // Parents component
            c->parent = this;

            // Adds component to components array
            std::unique_ptr<Component> uPtr {c};
            components.emplace_back(std::move(uPtr));

            compArr[getComponentTypeID<T>()] = c;
            compBitset[getComponentTypeID<T>()] = true;

            // Inits the component and returns pointer to component
            c->init();
            return *c;
        }

        template<typename T> T& getComponent() const {
            // Gets the component from component array
            auto ptr(compArr[getComponentTypeID<T>()]);

            // Returns pointer to component
            return *static_cast<T*>(ptr);
        }

        void update() {
            // Goes through all the components (for this entity) calls their update method
            for(auto &c : components) c->update();
        }

        void draw() {
            // Goes through all the components (for this entity) calls their draw method
            for(auto &c : components) c->draw();
        }

        inline bool isActive() {return active;}
        void destroy() {active = false;}
};

// Manager class
class Manager {
    private:
        std::vector<std::unique_ptr<Entity>> entities;

    public:
        void update() {
            // Goes through all the entities and calls their update function
            for(auto &e : entities) e->update();
        }

        void draw() {
            // Goes through all the entities and calls their draw function
            for(auto &e : entities) e->draw();
        }

        void refresh() {
            entities.erase(
                std::remove_if(
                    std::begin(entities),
                    std::end(entities),
                    [](const std::unique_ptr<Entity> &mEntity) {
                        return !mEntity->isActive();
                    }
                ),
                std::end(entities)
            );
        }

        Entity &addEntity() {
            // Adds a new entity
            Entity *e = new Entity();
            std::unique_ptr<Entity> uPtr {e};

            entities.emplace_back(std::move(uPtr));
            return *e;
        }
};