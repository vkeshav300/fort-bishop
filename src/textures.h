// Comments found in "assets.cpp"
#pragma once

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "game.h"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char *filename);

    static SDL_Texture *LoadFont(TTF_Font *font, SDL_Color color, const char *text);

    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};