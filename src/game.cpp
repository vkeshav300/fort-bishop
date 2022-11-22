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

std::vector<HitboxComponent*> Game::collisions;

// Player Creation
auto &Player(manager.addEntity());

// Render layer enum
enum groupLabels : std::size_t {
    groupMap = 0,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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
    Map::LoadMap("assets/tilemaps/fort-bishop.map", 16, 16);
    
    // Player
    Player.addComponent<TransformComponent>(1, false, 10);
    Player.addComponent<SpriteComponent>("assets/textures/entities/player/idle.png");
    Player.addComponent<ControlComponent>();
    Player.addComponent<HitboxComponent>("player");
    Player.addGroup(groupPlayers);
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

    for(auto hc: collisions) {
        if(hc != PlayerHitboxComponent) Collision::AABB(Player.getComponent<HitboxComponent>(), *hc);
    }
}

// Gets entities from groups
auto &players(manager.getEntitiesFromGroup(groupPlayers));
auto &mapEntities(manager.getEntitiesFromGroup(groupMap));
auto &enemies(manager.getEntitiesFromGroup(groupEnemies));

// Renders everything to the screen
void Game::render() {
    // Clears renderer
    SDL_RenderClear(renderer);
    
    /*
    Loads all entities for rendering
    Order matters, the last group to be rendered will have higher rendering priority than the others.
    */
    for(auto &e : mapEntities) {e->draw();}
    for(auto &e : enemies) {e->draw();}
    for(auto &e : players) {e->draw();}

    // Renders all changes in this frame
    SDL_RenderPresent(renderer);
}

// Runs on game being quit
void Game::clean(double shutdown_delay) {
    // Destructs Player
    Player.destroy();
    std::cout << " " << std::endl;
    std::cout << "1: Player Deactivated" << std::endl;

    manager.refresh();
    std::cout << "2: Manager Refreshed" << std::endl;

    // Destroys SDL Window
    SDL_DestroyWindow(window);
    std::cout << "3: Window destroyed" << std::endl;

    // Destroys SDL Renderer
    SDL_DestroyRenderer(renderer);
    std::cout << "4: Renderer destroyed" << std::endl;

    // Quits SDL
    SDL_Quit();
    std::cout << "5: Game Cleaned" << std::endl;

    // Delay to see confirmation messages
    float shutdown_ms = shutdown_delay * 1000;
    std::cout << "6: Shutting down in " << shutdown_ms << " ms" << std::endl;
    SDL_Delay(shutdown_ms);
}

void Game::addTile(int id, int x, int y) {
    auto &tile = manager.addEntity();
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}