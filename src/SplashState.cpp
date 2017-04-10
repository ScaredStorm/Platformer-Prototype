#include "SplashState.h"
#include "SelectionState.h"
#include "GameState.h"

SplashState::SplashState(Application* app)
    : m_app(app)
{
    
    oldTime = SDL_GetTicks();
}

void SplashState::update()
{
#ifdef _DEBUG
	m_app->getStateManager()->push<SelectionState>(m_app);
#endif

    if(oldTime + 1500 < SDL_GetTicks())
    {
		m_app->getStateManager()->push<SelectionState>(m_app);
    }
}

void SplashState::render(SDL_Renderer *renderer)
{
	//SDL_SetRenderDrawColor(renderer, 118, 118, 118, 255);
	m_app->getTextureManager()->renderTexture("SplashScreen", renderer, 0, 0, 320, 180);
}

void SplashState::handleInput(SDL_Event &e)
{
}