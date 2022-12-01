#include "AssetManager.h"
#include <SDL_image.h>
#include "SDLManager.h"

std::map<std::string, Sprite*> AssetManager::sprites = std::map<std::string, Sprite*>();


void AssetManager::Init()
{
}

void AssetManager::Clear()
{
	for (auto tex : sprites)
	{
		if (tex.second->texture != nullptr) SDL_DestroyTexture(tex.second->texture);
	}
	sprites.clear();
}

Sprite* AssetManager::GetSprite(std::string filename)
{
	std::string fullPath = "Assets/" + filename + ".png";

	if (sprites[fullPath] == nullptr)
	{
		SDL_Surface* pTempSurface = IMG_Load(fullPath.c_str());
		if (pTempSurface == 0) 
		{
			std::cout << "Not Found 1" << std::endl;
			return nullptr;
		}
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), pTempSurface);
		SDL_FreeSurface(pTempSurface);
		if (pTexture != 0) return new Sprite(pTexture);
		else
		{
			std::cout << "Not Found 2" << std::endl;
			return nullptr;
		}
	}

	return 	sprites[fullPath];
}
