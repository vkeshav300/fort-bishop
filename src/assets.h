// Comments found in "textures.cpp"
#pragma once

class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char *filename);
        static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};

class SoundManager {
    public:
        static void LoadSound(const char *filename);
        static void Play();
};