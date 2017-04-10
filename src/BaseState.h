#ifndef _BASESTATE_H_
#define _BASESTATE_H_

#include <stdio.h>
#include <SDL.h>

class BaseState
{
public:
    virtual void update() = 0;
    virtual void handleInput(SDL_Event &e) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};

#endif
