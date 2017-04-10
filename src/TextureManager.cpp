#include "TextureManager.h"

void TextureManager::addTexture(const std::string &key, const std::string &path, SDL_Renderer *renderer)
{
    SDL_Texture* temp = IMG_LoadTexture(renderer, path.c_str());
    if(temp == nullptr)
    {
        return;
    }
    
    m_textures[key] = temp;
}

void TextureManager::removeTexture(const std::string &key)
{
	if(m_textures.find(key) != m_textures.end())
	{
		m_textures[key] = nullptr;
		m_textures.erase(key);
	}
}

void TextureManager::renderTexture(const std::string& key, SDL_Renderer *renderer, int x, int y, int w, int h, SDL_RendererFlip flip)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = src.y = 0;
	src.w = dst.w = w;
	src.h = dst.h = h;
	dst.x = x;
	dst.y = y;

	SDL_RenderCopyEx(renderer, m_textures[key], &src, &dst, 0.0, NULL, flip);
}

void TextureManager::renderTextureFrame(const std::string& key, SDL_Renderer *renderer, int x, int y, int w, int h, int r, int c, SDL_RendererFlip flip)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = c * w;
	src.y = r * h;
	src.w = dst.w = w;
	src.h = dst.h = h;
	dst.x = x;
	dst.y = y;
    
	SDL_RenderCopyEx(renderer, m_textures[key], &src, &dst, 0.0, NULL, flip);
}

std::string TextureManager::getBasePath(const std::string& path)
{
	std::string basePath;
	if (basePath.empty())
	{
		char *base = SDL_GetBasePath();
		if (base)
		{
			basePath = base;
			SDL_free(base);
		}
		else
		{
			std::printf("Base path error: %s\n", SDL_GetError());
			return "";
		}
		basePath.append(path);
	}
	return basePath;
}

SDL_Texture* TextureManager::getTexture(const std::string& key)
{
	if (m_textures.find(key) != m_textures.end())
		return m_textures[key];
	else
		return nullptr;
}