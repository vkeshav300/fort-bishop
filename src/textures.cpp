// Including
#include "textures.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename)
{
    SDL_Surface *tempSurface = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

SDL_Texture *TextureManager::LoadFont(TTF_Font *font, SDL_Color color, const char *text)
{
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    double nulldouble;
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, nulldouble, nullptr, flip);
}