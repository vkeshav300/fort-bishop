#pragma once

#include <typeinfo>

// Base component class
class Component {
    public:
        // Entity *parent = nullptr;

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
                components[componentsNum - 1] = newComponent;
                // components[componentsNum - 1].parent = *this;
                components[componentsNum - 1].init();

                // Deletes the newComponent to save space in memory
                delete &newComponent;
                
                // components[componentsNum - 1]->parent = *this;
            }
        }

        bool hasComponent(auto searchComponent) {
            // Loops through array and searches for specific component
            for(int i = 0; i < componentsNum; i++) {
                if(typeid(components[i]) == typeid(*searchComponent)) {return true;}
            }

            return false;
        }

        auto getComponent(auto searchComponent) {
            for(int i = 0; i < componentsNum; i++) {
                if(typeid(components[i]) == typeid(*searchComponent)) {return components[i];}
            }

            return NULL;
        }

        void update() {
            for(int i = 0; i < componentsNum; i++) {
                components[i].update();
            }
        }
};