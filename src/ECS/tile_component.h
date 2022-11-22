#pragma once

#include "components.h"

class TileComponent : public Component {
    private:
        TransformComponent *transform;
        SpriteComponent *sprite;

    public:
        SDL_Rect tileRect;
        int tileId;
        const char *path;

        // Constructors
        TileComponent() = default;

        TileComponent(int x, int y, int w, int h, int id) {
            // Setting tile properties
            tileRect.x = x;
            tileRect.y = y;
            tileRect.w = w;
            tileRect.h = h;
            tileId = id;

            // Certain integers are mapped to a tile sprite
            switch(tileId) {
                case 0:
                    path = "assets/textures/tiles/grass.png";
                    break;

                case 1:
                    path = "assets/textures/tiles/dirt.png";
                    break;

                case 2:
                    path = "assets/textures/tiles/water.png";
                    break;

                default:
                    break;
            };
        }

        // Initializes component
        void init() override {
            // Adds and gets "TransformComponent"
            parent->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
            transform = &parent->getComponent<TransformComponent>();

            // Adds and gets "SpriteComponent"
            parent->addComponent<SpriteComponent>(path);
            sprite = &parent->getComponent<SpriteComponent>();
        }


};