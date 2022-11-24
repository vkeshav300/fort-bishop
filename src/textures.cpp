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
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0d, nullptr, flip);
}