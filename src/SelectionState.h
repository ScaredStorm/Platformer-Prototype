#ifndef _SELECTIONSTATE_H_
#define _SELECTIONSTATE_H_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <memory>

#include <SDL.h>

#include "BaseState.h"
#include "Application.h"

class SelectionState : public BaseState
{
public:
	SelectionState(Application* app);

	void update();
	void render(SDL_Renderer *renderer);
	void handleInput(SDL_Event &e);
private:
	Application* m_app;

private:
	int mx;
	int my;

	int m_sel;
	bool select;
};

#endif
