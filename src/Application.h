#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "StateManager.h"
#include "TextureManager.h"

class Application
{
public:
    Application();
    
    bool init();
	void loadContent();

    void run();
    void handleInput();
    void update();
    void render();
    
    StateManager<Application>* getStateManager();
	TextureManager* getTextureManager();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    
    StateManager<Application> m_stateManager;
	TextureManager m_texManager;
    
private:
    bool m_isRunning;
    
    const unsigned VERSION_MAJOR = 0;
    const unsigned VERSION_MINOR = 1;
    const unsigned VERSION_BUILD = 2;
    const unsigned VERSION_REVISION = 2;
};

#endif
