#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <memory>

#include <SDL.h>

#include "BaseState.h"
#include "Application.h"
#include "Player.h"
#include "Level.h"

class GameState : public BaseState
{
public:
    GameState(Application* app);
    
    void update();
    void render(SDL_Renderer *renderer);
    void handleInput(SDL_Event &e);
private:
    Application* m_app;
    
private:
    Player p;
    Level l;

private:
	std::vector<std::shared_ptr<Entity>> _entities;
	int mx;
	int my;
};

#endif
