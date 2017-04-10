#ifndef _SPLASHSTATE_H_
#define _SPLASHSTATE_H_

#include <iostream>
#include <stdio.h>
#include <math.h>

#include <SDL.h>

#include "BaseState.h"
#include "Application.h"

class SplashState : public BaseState
{
public:
    SplashState(Application* app);
    
    void update();
    void render(SDL_Renderer *renderer);
    void handleInput(SDL_Event &e);
private:
    Application* m_app;
    
private:
    // test vars
    float time;
    float inc;
    int oldTime;
};

#endif
