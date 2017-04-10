#ifndef _TILE_H_
#define _TILE_H_

#include <stdio.h>
#include <SDL.h>

#include "TextureManager.h"

class Tile
{
public:
    void render(SDL_Renderer* renderer, TextureManager* man);
    
public:
    int tid;
    int x;
    int y;
    int z;
};

#endif
