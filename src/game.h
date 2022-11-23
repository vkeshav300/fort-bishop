// Other comments found in "game.cpp"
#pragma once

// Including
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"

#include <iostream>
#include <cmath>
#include <vector>

// Forward declaration of "ColliderComponent"
class HitboxComponent;

// Enum directions
enum eDir {
    IDLE = 0,
    UP,
    DOWN,
    RIGHT,
    LEFT
};

// Game class
class Game {
    // Private variables
    private:
        int cnt;
        bool isRunning;
        SDL_Window *window;

    // Public variables and methods
    public:
        // All hitboxes (for all entities)
        static std::vector<HitboxComponent*> collisions;

        // Constructor
        Game();

        // Destructor
        ~Game();

        // Init method
        void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

        // Handles all events
        void handleEvents();

        // Updates everything
        void update();

        // Renders everything
        void render();

        // Cleans up at the end of running
        void clean(double shutdown_delay);

        // Returns if the game is running
        inline bool running() {return isRunning;}

        static void addTile(int id, int x, int y);

        static SDL_Renderer *renderer;
        static SDL_Event event;
};