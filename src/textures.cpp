// Including
#include "textures.h"

// Loading a texture
SDL_Texture* TextureManager::LoadTexture(const char *filename) {
    SDL_Surface *tempSurface = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

// Drawing a texture
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    /*
    When passing in NULL for argument 5 in SDL_RenderCopyEx, it will raise an error when compiling.
    To get around this, creating a double variable and not assigning it a value, then passing that
    double in will stop any errors.
    */
    double nulldouble;
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, nulldouble, nullptr, flip);
}