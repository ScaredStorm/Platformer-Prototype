#include "Player.h"

Player::Player(Level *level, SDL_Texture* sprite, float x, float y, int id)
	: Entity(sprite, x, y)
	, m_level(level)
{
	std::printf("Player position: %fx%f\n", m_x, m_y);
    m_leftPressed = false;
    m_rightPressed = false;
    m_upPressed = false;
    m_downPressed = false;
    m_onGround = false;
    
    m_xVel = 0;
    m_yVel = 0;
    
    m_width = 16;
    m_height = 16;

	m_playerId = id;

	m_dir = 1;
	flip = SDL_FLIP_NONE;
}

void Player::update()
{
    checkCollision();
    
    m_x += m_xVel;
    m_y += m_yVel;
    
    if(!m_onGround)
    {
		if (m_yVel < 5.0f)
			m_yVel += 0.5f;
    }
    
    /* PLAYER MOVEMENT */
    if(m_rightPressed)
    {
		m_dir = 1;
		m_xVel = 1.0f;
		flip = SDL_FLIP_NONE;
    }
    if(m_leftPressed)
    {
		m_dir = -1;
		m_xVel = -1.0f;
		flip = SDL_FLIP_HORIZONTAL;
    }

	if (!m_rightPressed && !m_leftPressed)
	{
		m_xVel = 0.0f;
	}
    
	if (m_upPressed && m_onGround)
		m_yVel = -6.0f;

	std::printf("yVel: %f, xVel: %f\n", m_yVel, m_xVel);
}

void Player::setPos(int x, int y)
{
	m_x = (float)x;
	m_y = (float)y;
}

void Player::handleInput(SDL_Event &e)
{
    // Key Pressed
    if(e.type == SDL_KEYDOWN)
    {
        SDL_Keycode k = e.key.keysym.sym;
        switch(k)
        {
			case SDLK_z:
                m_upPressed = true;
                break;
                
            case SDLK_DOWN:
                //m_downPressed = true;
                break;
                
            case SDLK_LEFT:
                m_leftPressed = true;
				
                break;
                
            case SDLK_RIGHT:
                m_rightPressed = true;
                break;
        }
    }
    
    // Key Released
    if(e.type == SDL_KEYUP)
    {
        SDL_Keycode k = e.key.keysym.sym;
        switch(k)
        {
            case SDLK_z:
                m_upPressed = false;
                break;
                
            case SDLK_DOWN:
                //m_downPressed = false;
                break;
                
            case SDLK_LEFT:
                m_leftPressed = false;
                m_xVel = 0.0f;
                break;
                
            case SDLK_RIGHT:
                m_rightPressed = false;
                m_xVel = 0.0f;
                break;
        }
    }
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_Rect src;
    SDL_Rect dst;
    
	src.x = m_playerId * 16;
    src.y = 0;
    src.w = dst.w = 16;
    src.h = dst.h = 16;
    dst.x = m_x;
    dst.y = m_y;
    
    SDL_RenderCopyEx(renderer, m_sprite, &src, &dst, 0.0, NULL, flip);
    
    // render weapon
    SDL_Rect wsrc;
    SDL_Rect wdst;
    wsrc.x = m_playerId * 16;
    wsrc.y = 32;
    wsrc.w = wdst.w = 16;
    wsrc.h = wdst.h = 16;
    wdst.x = m_x+(3 * m_dir);
    wdst.y = m_y;
    SDL_RenderCopyEx(renderer, m_sprite, &wsrc, &wdst, 0.0, NULL, flip);

#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, m_x + 8, m_y + 16, m_x + 8, m_y + 16 + m_yVel);
#endif
}

void Player::checkCollision()
{
    int currRow = (int)m_y/m_level->getTileSize();
    int currColumn = (int)m_x/m_level->getTileSize();
    
    int xdest, ydest, xtemp, ytemp;
    xdest = m_x + m_xVel;
    ydest = m_y + m_yVel;

	xtemp = m_x;
	ytemp = m_y;

	calculateCorners(m_x, ydest);
	if (m_yVel < 0)
	{
		if (m_topLeft || m_topRight)
		{
			m_yVel = 0;
		}
	}

	if (m_yVel > 0)
	{
		if (m_bottomLeft || m_bottomRight)
		{
			m_yVel = 0;
			m_onGround = true;
		}
	}

	if (!m_bottomLeft && !m_bottomRight)
	{
		m_onGround = false;
	}
	else
	{
		m_onGround = true;
		m_yVel = 0;
	}

    calculateCorners(xdest, m_y);
	if(m_xVel > 0)
    {
        if(m_topRight || m_bottomRight)
        {
            m_xVel = 0;
            //m_x = currColumn * m_level->getTileSize();
        }
    }
    if(m_xVel < 0)
    {
        if(m_topLeft || m_bottomLeft)
        {
            m_xVel = 0;
            //m_x = currColumn * m_level->getTileSize();
        }
    }
}

void Player::calculateCorners(float x, float y)
{
    int left = (int)(x+2)/m_level->getTileSize();
    int right = (int)(x+m_width-2)/m_level->getTileSize();
    int top = (int)(y+4)/m_level->getTileSize();
    int bottom = (int)(y+m_height-1)/m_level->getTileSize();
    
    bool tl = m_level->canCollide(left, top);
    bool tr = m_level->canCollide(right, top);
    bool bl = m_level->canCollide(left, bottom);
    bool br = m_level->canCollide(right, bottom);
    
    m_topLeft = tl;
    m_topRight = tr;
    m_bottomLeft = bl;
    m_bottomRight = br;
}