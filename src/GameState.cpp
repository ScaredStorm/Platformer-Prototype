#include "GameState.h"
#include "Globals.h"
#include "SelectionState.h"

GameState::GameState(Application* app)
    : m_app(app)
    , l(16)
    , p(&l, m_app->getTextureManager()->getTexture("Player"), 16*16, 17, g_playerId) // y = 180-16-4
{
    l.loadMap(m_app->getTextureManager()->getBasePath("/Assets/Levels/map.txt").c_str());
}

void GameState::update()
{
    p.update();
}

void GameState::render(SDL_Renderer *renderer)
{

    l.render(renderer, m_app->getTextureManager());
    p.render(renderer);
    
    m_app->getTextureManager()->renderTextureFrame("UI", renderer, 4, 4, 64, 8, 0, 0);
    m_app->getTextureManager()->renderTextureFrame("UI", renderer, 4, 13, 64, 8, 1, 0);

#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, my/4, 1280, my/4);
	SDL_RenderDrawLine(renderer, mx/4, 0, mx/4, 720);
#endif

	SDL_SetRenderDrawColor(renderer, 153, 245, 255, 255);
}

void GameState::handleInput(SDL_Event &e)
{
    p.handleInput(e);

	if (e.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&mx, &my);
	}

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			m_app->getStateManager()->pop();
		}
	}

#ifdef _DEBUG
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&mx, &my);

		p.setPos(mx/4-8, my/4-8);
	}
#endif
}