#pragma once

#include <typeinfo>

class Entity;
class Component;

// Base component class
class Component {
    public:
        Entity *parent = nullptr;

        Component() {}
        
        virtual void init() {}
        virtual void update() {}
};

// Base entity class
class Entity {
    public:
        // Where entities components are stored
        Component components[25];
        int componentsNum = 0;

        // Constructor
        Entity() {}

        // Adds a components
        void addComponent(auto newComponent) {
            if(!componentsNum == 25) {
                // Adds one to the total components
                componentsNum++;
                
                // Copies newComponent into the list of components
                components[componentsNum - 1] = dynamic_cast<TransformComponent>(newComponent);

                // Deletes the newComponent to save space in memory
                delete &newComponent;

                // Initializes component
                components[componentsNum - 1].parent = this;
                components[componentsNum - 1].init();                
            }
        }

        TransformComponent *getTransform() {
            for(int i = 0; i < componentsNum; i++) {
                if(typeid(components[i]) == typeid(TransformComponent())) {return *components[i];}
            }
        }

        void update() {
            for(int i = 0; i < componentsNum; i++) {
                components[i].update();
            }
        }
};