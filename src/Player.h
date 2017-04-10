#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <stdio.h>
#include <SDL.h>

#include "Entity.h"
#include "Level.h"

class Player : public Entity
{
public:
	Player(Level *level, SDL_Texture* sprite, float x, float y, int id);

	void update() override;
	void render(SDL_Renderer* renderer) override;
	void handleInput(SDL_Event &e) override;

	void setPlayerId();
	void setPos(int x, int y);
private:
    float m_yVel;
    float m_xVel;
    
    Level* m_level;

private:
    bool m_leftPressed;
    bool m_rightPressed;
    bool m_upPressed;
    bool m_downPressed;
    bool m_onGround;
    
	int m_dir;
	SDL_RendererFlip flip;

	int m_playerId;

    // Collision
private:
    int m_width;
    int m_height;
    
    bool m_topLeft;
    bool m_bottomLeft;
    bool m_topRight;
    bool m_bottomRight;
    
    void checkCollision();
    void calculateCorners(float x, float y);
};

#endif