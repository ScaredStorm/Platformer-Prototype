#include "Tile.h"

void Tile::render(SDL_Renderer *renderer, TextureManager* man)
{
    if(tid != -1)
    {
        man->renderTextureFrame("Tiles", renderer, x, y, 16, 16, tid/4, tid%4);
    }
}