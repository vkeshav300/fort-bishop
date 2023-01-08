#pragma once

#include "../components.h"
#include "../../textures.h"
#include "../../custom_types/vector.h"

class UiLabel : public Component
{
public:
    // ? Text Label Properties
    const char *text;

    bool camera_interact = false;

    vector position, size;

    TTF_Font *font;
    SDL_Color *color;
    
    // ? To render the font, the font must be converted into a SDL_Texture
    SDL_Texture *texture;

    SDL_Rect srcRect, destRect;

    UiLabel() = default;

    UiLabel(const char *font_id, const char *color_id, const char *display_text, int w, int h, int xPos, int yPos) : text(display_text)
    {
        // * Getting font properties from Game::assets
        font = Game::assets->fonts[font_id];
        color = Game::assets->colors[color_id];

        // ? Size and position
        size.x = w;
        size.y = h;

        position.x = xPos;
        position.y = yPos;

        srcRect.x = srcRect.y = 0;
    }

    UiLabel(const char *font_id, const char *color_id, const char *display_text, int w, int h, int xPos, int yPos, bool interacts_with_camera) : text(display_text), camera_interact(interacts_with_camera)
    {
        // * Getting font properties from Game::assets
        font = Game::assets->fonts[font_id];
        color = Game::assets->colors[color_id];

        // ? Size and position
        size.x = w;
        size.y = h;

        position.x = xPos;
        position.y = yPos;

        srcRect.x = srcRect.y = 0;
    }

    ~UiLabel()
    {
        SDL_DestroyTexture(texture);
    }

    void updatePos(int xPos, int yPos)
    {
        position.x = xPos;
        position.y = yPos;
    }

    void updateSize(int w, int h)
    {
        size.x = w;
        size.y = h;
    }

    void updateText(const char *new_text)
    {
        text = new_text;
    }

    void updateColor(const char *id)
    {
        color = Game::assets->colors[id];
    }

    void update() override
    {
        // Updates size
        srcRect.w = destRect.w = size.x;
        srcRect.h = destRect.h = size.y;

        // Changes position according to Game::camera
        if (camera_interact)
        {
            destRect.x = position.x - Game::camera.x;
            destRect.y = position.y - Game::camera.y;
            
            return;
        }

        destRect.x = position.x;
        destRect.y = position.y;

        texture = TextureManager::LoadFont(font, *color, text);
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};