#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

#include <SDL.h>

#include "Tile.h"

class Level
{
public:
    Level(int tileSize);
    
    void loadMap(const char* map);
    bool canCollide(int x, int y);
    int getTileSize();
    
    void render(SDL_Renderer* renderer, TextureManager* man);
    
private:
    int m_tileSize;
    std::vector<std::vector<std::vector<Tile>>> m_level;
    
    int m_width;
    int m_height;
    int m_depth;
};

#endif