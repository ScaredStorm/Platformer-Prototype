#include "Application.h"
#include "Utils.h"
#include "SplashState.h"

Application::Application()
{
    m_isRunning = false;
    if(init())
    {
        m_stateManager.push<SplashState>(this);
        m_isRunning = true;
    }
}

bool Application::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Initialization error: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Initialized SDL\n";
    
    std::string str = "AdventureGame - v";
    str += toString(VERSION_MAJOR);
    str += ".";
    str += toString(VERSION_MINOR);
    str += ".";
    str += toString(VERSION_BUILD);
    str += ".";
    str += toString(VERSION_REVISION);
    
    m_window = SDL_CreateWindow(str.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if(m_window == nullptr)
    {
        SDL_Quit();
        std::cerr << "SDL Window creation error: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Created window with dimensions: " << 1280 << "x" << 720 << std::endl;
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        std::cerr << "SDL Renderer creation error: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Created renderer\n";
    
    if((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        std::cerr << "Image library failed to load: " << IMG_GetError() << std::endl;
        return false;
    }
    std::cout << "Loaded image library\n";
    
    SDL_SetRenderDrawColor(m_renderer, 118, 118, 118, 255);
    SDL_RenderSetScale(m_renderer, 4, 4);
    
	loadContent();

    return true;
}

void Application::loadContent()
{
	m_texManager.addTexture("SplashScreen", TextureManager::getBasePath("/Assets/Graphics/Splash.png"), m_renderer);
    m_texManager.addTexture("Player", TextureManager::getBasePath("/Assets/Graphics/SpritesheetPlayer.png"), m_renderer);
    m_texManager.addTexture("UI", TextureManager::getBasePath("/Assets/Graphics/UIElements.png"), m_renderer);
    m_texManager.addTexture("Tiles", TextureManager::getBasePath("/Assets/Graphics/Tileset.png"), m_renderer);
	m_texManager.addTexture("GUI", TextureManager::getBasePath("/Assets/Graphics/GUI.png"), m_renderer);
	m_texManager.addTexture("TouchControls", TextureManager::getBasePath("/Assets/Graphics/TouchControls.png"), m_renderer);
	m_texManager.addTexture("Quotes", TextureManager::getBasePath("/Assets/Graphics/quotes.png"), m_renderer);
	m_texManager.addTexture("Icons", TextureManager::getBasePath("/Assets/Graphics/Icons.png"), m_renderer);
}

void Application::run()
{
    while(m_isRunning)
    {
        handleInput();
        update();
        render();
    }
}

void Application::handleInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            m_isRunning = false;
        
        m_stateManager.handleInput(e);
    }
}

void Application::update()
{
    m_stateManager.update();
	//SDL_Delay(500);
}

void Application::render()
{
    SDL_RenderClear(m_renderer);
    
    m_stateManager.render(m_renderer);
    
    // Clear color
	//SDL_SetRenderDrawColor(m_renderer, 118, 118, 118, 255);
    SDL_RenderPresent(m_renderer);
}

StateManager<Application>* Application::getStateManager()
{
	return &m_stateManager;
}

TextureManager* Application::getTextureManager()
{
	return &m_texManager;
}

SDL_Window* Application::getWindow()
{
    return m_window;
}

SDL_Renderer* Application::getRenderer()
{
    return m_renderer;
}