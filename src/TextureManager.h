#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <stdio.h>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
    void addTexture(const std::string &key, const std::string &path, SDL_Renderer* renderer);
    void removeTexture(const std::string &key);
    
	void renderTexture(const std::string &key, SDL_Renderer *renderer, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderTextureFrame(const std::string &key, SDL_Renderer *renderer, int x, int y, int w, int h, int r, int c, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
	static std::string getBasePath(const std::string &path);
	SDL_Texture *getTexture(const std::string &key);

private:
    std::map<std::string, SDL_Texture*> m_textures;
};

#endif
