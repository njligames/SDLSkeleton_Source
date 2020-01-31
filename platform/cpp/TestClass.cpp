#include "TestClass.h"

#include "SDL.h"

#include <string>

static SDL_Texture *
LoadTexture(SDL_Renderer *renderer, char *file, SDL_bool transparent)
{
    SDL_Surface *temp;
    SDL_Texture *texture;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load %s: %s", file, SDL_GetError());
        return NULL;
    }

    /* Set transparent pixel as the pixel at (0,0) */
    if (transparent) {
        if (temp->format->palette) {
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
        } else {
            switch (temp->format->BitsPerPixel) {
            case 15:
                SDL_SetColorKey(temp, SDL_TRUE,
                                (*(Uint16 *) temp->pixels) & 0x00007FFF);
                break;
            case 16:
                SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
                break;
            case 24:
                SDL_SetColorKey(temp, SDL_TRUE,
                                (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
                break;
            case 32:
                SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
                break;
            }
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return NULL;
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return texture;
}

TestClass::TestClass(int n) : mNum(n){}
TestClass::~TestClass(){}

bool TestClass::loadfile(SDL_Renderer *renderer) {
    int w,h;
    
    SDL_Texture *sprite = LoadTexture(renderer, "resources/sample.bmp", SDL_TRUE);
    if(nullptr == sprite) {
        SDL_Log("Could not find the sprite");
        return false;
    } else {
        SDL_QueryTexture(sprite, NULL, NULL, &w, &h);
        SDL_Log("Width: %d, Height: %d", w, h);
    }
    return true;
    
}

void TestClass::reset(int n){mNum = n;}
int TestClass::increment(int n){mNum += n; return mNum;}

