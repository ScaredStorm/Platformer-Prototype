#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <iostream>
#include <SDL.h>

class Entity
{
public:
    Entity(SDL_Texture* sprite, float x, float y);
	
	virtual void update() = 0;
	virtual void handleInput(SDL_Event &e) = 0;
	virtual void render(SDL_Renderer *renderer) = 0;
    
protected:
	float m_x;
	float m_y;

	SDL_Texture *m_sprite;
};

#endif