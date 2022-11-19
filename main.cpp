// Entire file puts together game. The actual work goes on in header (.h) and other C++ (.cpp) files
#include "src/game.h"

// Creating game pointer
Game *game = nullptr;
const char *title = "Fort Bishop";

int main(int argc, char** argv) {
    // FPS limiting
    const int FPS = 144;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Initializing game
    game = new Game();
    game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    // Runs every frame, when game->isRunning is set to false (game->handleEvents()), it will exit the loop and run game.clean()
    while(game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        // Makes sure the loop only runs one time per frame
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Cleans game after running stopped
    game->clean(2.5);

    return 0;
}