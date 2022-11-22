// Including
#include "game.h"
#include "assets.h"
#include "tilemap.h"
#include "vector.h"
#include "collision.h"
#include "ECS/components.h"

// Creating neccessary objects and variables
Map *map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<HitboxComponent*> Game::borders;

// Player Creation
auto &Player(manager.addEntity());
auto &testWall(manager.addEntity());

// Tiles
auto &tile0(manager.addEntity());
auto &tile1(manager.addEntity());
auto &tile2(manager.addEntity());

// Game Constructor
Game::Game() {}

// Game Deconstructor
Game::~Game() {}

// Init method
void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
    // Checks for fullscreen
    int flags = 0;
    if (fullscreen) {flags = SDL_WINDOW_FULLSCREEN;}

    // Initializes "SDL_INIT_EVERYTHING"
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {std::cerr << "Failed at SDL_Init()" << std::endl; return;}

    // Creates Window
    window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if (!window)
    {std::cerr << "Failed at SDL_CreateWindow()" << std::endl; return;}

    // Creates renderer
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (!renderer)
    {std::cerr << "Failed at SDL_CreateRenderer()" << std::endl; return;}
    
    // Draws background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Sets isRunning to true to game loop can start
    isRunning = true;

    // Setting up neccessary objects and variables
    map = new Map();

    // Tiles
    tile0.addComponent<TileComponent>(200, 200, 32, 32, 2);
    tile0.addComponent<HitboxComponent>("water");
    tile1.addComponent<TileComponent>(150, 150, 32, 32, 2);
    tile1.addComponent<HitboxComponent>("water");
    tile2.addComponent<TileComponent>(250, 250, 32, 32, 2);
    tile2.addComponent<HitboxComponent>("water");

    // Player
    Player.addComponent<TransformComponent>(1, false, 10);
    Player.addComponent<SpriteComponent>("assets/textures/entities/player/idle.png");
    Player.addComponent<ControlComponent>();
    Player.addComponent<HitboxComponent>("player");

    // Wall
    testWall.addComponent<TransformComponent>(300, 300, 20, 300, true, 1);
    testWall.addComponent<SpriteComponent>("assets/textures/tiles/dirt.png");
    testWall.addComponent<HitboxComponent>("testwall");
}

// Handles all events
void Game::handleEvents() {
    // Gets all events
    SDL_PollEvent(&event);
    switch (event.type)
    {
        // If the game is quitting set isRunning to false
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

// Updates everything (every frame)
void Game::update() {
    manager.update();
    manager.refresh();

    // Handles all collisions
    HitboxComponent *PlayerHitboxComponent = &Player.getComponent<HitboxComponent>();

    for(auto hc: borders) {
        if(hc != PlayerHitboxComponent) Collision::AABB(Player.getComponent<HitboxComponent>(), *hc);
    }
}

// Renders everything to the screen
void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

// Runs on game being quit
void Game::clean(double shutdown_delay) {
    // Destructs Player
    delete &Player;
    std::cout << " " << std::endl;
    std::cout << "Player Destructed" << std::endl;

    // Destroys SDL Window
    SDL_DestroyWindow(window);
    std::cout << "Window destroyed" << std::endl;

    // Destroys SDL Renderer
    SDL_DestroyRenderer(renderer);
    std::cout << "Renderer destroyed" << std::endl;

    // Quits SDL
    SDL_Quit();
    std::cout << "Game Cleaned, Shutting Down" << std::endl;

    // Delay to see confirmation messages
    float shutdown_ms = shutdown_delay * 1000;
    std::cout << "Shutting down in " << shutdown_ms << " ms" << std::endl;
    SDL_Delay(shutdown_ms);
}