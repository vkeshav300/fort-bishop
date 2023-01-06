// *  * src file
#include "collision.h"
#include "textures.h"
#include "tilemap.h"
#include "assets.h"
#include "./ECS/components.h"
#include "game.h"

// * Creating neccessary objects and variables
Map *map;

// * Player Game::camera
SDL_Rect Game::camera = {0, 0, 0, 0};

// * Entity Component System Manager
Manager *Game::manager = new Manager();

// * Assets Manager
AssetManager *Game::assets = new AssetManager(Game::manager);

// * SDL_Renderer (rendering things)
SDL_Renderer *Game::renderer = nullptr;

// * SDL_Event (keypresses, exiting, etc.)
SDL_Event Game::event;

// * All HitboxComponents (used in update() function for collision checks)
std::vector<Hitbox *> Game::collisions;

// * Player Creation
auto &Player(Game::manager->addEntity());

// * Game Constructor
Game::Game() {}

// * Game Deconstructor
Game::~Game() {}

// ? Initializes Game
void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    /* Initializing */
    // ! The following code initializes SDL and all its packages / modules
    // *  Checks for fullscreen
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // *  Initializes "SDL_INIT_EVERYTHING"
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed at SDL_Init()" << std::endl;
        return;
    }

    // *  Initializes "SDL2_TTF"
    if(TTF_Init() < 0)
    {
        std::cerr << "Failed at TTF_Init()" << std::endl;
    }

    // *  Creates Window
    window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if (!window)
    {
        std::cerr << "Failed at SDL_CreateWindow()" << std::endl;
        return;
    }

    // *  Creates renderer
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (!renderer)
    {
        std::cerr << "Failed at SDL_CreateRenderer()" << std::endl;
        return;
    }

    // *  Draws background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // *  Sets Game::camera width and height
    Game::camera.w = width;
    Game::camera.h = height;

    // *  Sets isRunning to true to game loop can start
    isRunning = true;

    /* Tilemap */
    // ! The following code creates the tilemap
    // *  Adds textures Game::assets
    assets->addTexture("tiles", "assets/textures/tiles/tile_atlas.png");
    assets->addTexture("player", "assets/textures/entities/player/player_atlas.png");

    // *  Constructs Map *map
    map = new Map("tiles", 3, 32);

    // *  Loads Map
    map->LoadMap("assets/tilemaps/fort-bishop.map", 25, 20);

    /* Player */
    // *  ! The following code creates the Player
    // *  Transform (position, velocity, size, etc.)
    Player.addComponent<Transform>(2, false, 10);

    // *  Animated Sprite
    Player.addComponent<Sprite>("player", true);
    Player.getComponent<Sprite>().addAnim(WALK_CYCLE);

    // *  Control & Hitbox
    Player.addComponent<Controller>();
    Player.addComponent<Hitbox>("player");

    // *  Rendering Group
    Player.addGroup(LAYER_PLAYER);

    /* Other Things */
    
}

// ? Handles all events
void Game::handleEvents()
{
    // *  Gets all events
    SDL_PollEvent(&event);
    switch (event.type)
    {
    // *  If the game is quitting set isRunning to false
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

// ? Updates everything (every frame)
void Game::update()
{
    Game::manager->update();
    Game::manager->refresh();

    // *  Handles Game::camera
    Transform *PlayerTransformComponent = &Player.getComponent<Transform>();
    Game::camera.x = PlayerTransformComponent->position.x - (Game::camera.w / 2);
    Game::camera.y = PlayerTransformComponent->position.y - (Game::camera.h / 2);

    if (Game::camera.x < 0)
        Game::camera.x = 0;
    if (Game::camera.y < 0)
        Game::camera.y = 0;
    if (Game::camera.x > Game::camera.w)
        Game::camera.x = Game::camera.w;
    if (Game::camera.y > Game::camera.h)
        Game::camera.y = Game::camera.h;

    // *  Handles all collisions
    Hitbox *PlayerHitboxComponent = &Player.getComponent<Hitbox>();

    for (auto hc : collisions)
    {
        if (hc != PlayerHitboxComponent)
            Collision::AABB(Player.getComponent<Hitbox>(), *hc);
    }
}

// *  Gets entities from groups
auto &inactiveUI(Game::manager->getEntitiesFromGroup(LAYER_UI_INACTIVE));
auto &players(Game::manager->getEntitiesFromGroup(LAYER_PLAYER));
auto &mapEntities(Game::manager->getEntitiesFromGroup(LAYER_MAP));
auto &enemies(Game::manager->getEntitiesFromGroup(LAYER_NPC));
auto &activeUI(Game::manager->getEntitiesFromGroup(LAYER_UI_ACTIVE));

// ? Renders everything to the screen
void Game::render()
{
    // *  Clears renderer
    SDL_RenderClear(renderer);

    /*
     * Loads all entities for rendering.
     * Order matters, the last group to be rendered will have higher rendering priority than the others.
     */
    for (auto &e : inactiveUI)
        e->draw();
    for (auto &e : mapEntities)
        e->draw();
    for (auto &e : enemies)
        e->draw();
    for (auto &e : players)
        e->draw();
    for (auto &e : activeUI)
        e->draw();

    // *  Renders all changes in this frame
    SDL_RenderPresent(renderer);
}

// ? Runs on game being quit
void Game::clean(double shutdown_delay)
{
    // *  Destructs Player
    Player.destroy();
    std::cout << " " << std::endl;
    std::cout << "1: Player Deactivated" << std::endl;

    Game::manager->refresh();
    std::cout << "2: Manager Refreshed" << std::endl;

    // *  Destroys SDL Window
    SDL_DestroyWindow(window);
    std::cout << "3: Window destroyed" << std::endl;

    // *  Destroys SDL Renderer
    SDL_DestroyRenderer(renderer);
    std::cout << "4: Renderer destroyed" << std::endl;

    // *  Quits SDL TTF
    TTF_Quit();
    std::cout << "5: SDL TTF Quit" << std::endl;

    // *  Quits SDL
    SDL_Quit();
    std::cout << "6: SDL Quit" << std::endl;

    // *  Delay to see confirmation messages
    float shutdown_ms = shutdown_delay * 1000;
    std::cout << "7: Shutting down in " << shutdown_ms << " ms" << std::endl;
    SDL_Delay(shutdown_ms);

    // *  Confirms that Game::clean() has run fully
    std::cout << "8: (7) Game::clean() confirmation" << std::endl;
}