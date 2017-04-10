#include "SelectionState.h"
#include "GameState.h"
#include "Globals.h"

SelectionState::SelectionState(Application *app)
	: m_app(app)
{
	select = false;
}

void SelectionState::update()
{
	std::printf("Selection: %d, GLOBAL ID: %d\n", m_sel, g_playerId);
	//g_playerId--;
}

void SelectionState::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect pbg{ (1280 / 4) / 2 - 32, (720 / 4) / 2 - 8, 64, 16 };
	SDL_RenderFillRect(renderer, &pbg);

	m_app->getTextureManager()->renderTextureFrame("Player", renderer, (1280 / 4) / 2 - 8, (720 / 4) / 2 - 8, 16, 16, 0, m_sel, SDL_FLIP_NONE);
	m_app->getTextureManager()->renderTextureFrame("GUI", renderer, (1280 / 4) / 2 - 8 - 48, (720 / 4) / 2 - 8, 16, 16, 0, 0, SDL_FLIP_NONE);
	m_app->getTextureManager()->renderTextureFrame("GUI", renderer, (1280 / 4) / 2 - 8 + 48, (720 / 4) / 2 - 8, 16, 16, 0, 1, SDL_FLIP_NONE);
	m_app->getTextureManager()->renderTextureFrame("GUI", renderer, (1280 / 4) / 2 - 32, (720 / 4) / 2 + 32, 64, 32, 1, 0, SDL_FLIP_NONE);

	m_app->getTextureManager()->renderTextureFrame("Quotes", renderer, (1280 / 4) / 2 - 80, (720 / 4) / 2+8, 160, 16, m_sel, 0, SDL_FLIP_NONE);
	m_app->getTextureManager()->renderTextureFrame("Icons", renderer, 8, 8, 16, 16, 0, 0);

	SDL_SetRenderDrawColor(renderer, 48, 221, 255, 255);
}

void SelectionState::handleInput(SDL_Event &e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&mx, &my);
		mx /= 4;
		my /= 4;
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (mx > (1280 / 4) / 2 - 8 - 48 && mx < (1280 / 4) / 2 - 8 - 48 + 16 && my >(720 / 4) / 2 - 8 && my < (720 / 4) / 2 - 8 + 16)
			{
				m_sel--;
				if (m_sel < 0)
					m_sel = 7;

				if (m_sel > 7)
					m_sel = 0;
			}
			if (mx >(1280 / 4) / 2 - 8 + 48 && mx < (1280 / 4) / 2 - 8 + 48 + 16 && my >(720 / 4) / 2 - 8 && my < (720 / 4) / 2 - 8 + 16)
			{
				m_sel++;
				if (m_sel < 0)
					m_sel = 7;

				if (m_sel > 7)
					m_sel = 0;
			}

			// play button
			if (mx > (1280 / 4) / 2 - 32 && mx < (1280 / 4) / 2 - 32 + 64 && my >(720 / 4) / 2 + 32 && my < (720 / 4) / 2 + 32 + 32)
			{
				g_playerId = m_sel;
				m_app->getStateManager()->push<GameState>(m_app);
			}

		}
	}

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_LEFT)
		{
			m_sel--;
			if (m_sel < 0)
				m_sel = 7;

			if (m_sel > 7)
				m_sel = 0;
		}

		if (e.key.keysym.sym == SDLK_RIGHT)
		{
			m_sel++;
			if (m_sel < 0)
				m_sel = 7;

			if (m_sel > 7)
				m_sel = 0;
		}

		if (e.key.keysym.sym == SDLK_SPACE)
		{
			g_playerId = m_sel;
			m_app->getStateManager()->push<GameState>(m_app);
		}
	}
}