#include "AssetManager.h"


std::map<std::string, Sprite*> AssetManager::sprites = std::map<std::string, Sprite*>();
std::map<std::string, TTF_Font*> AssetManager::fonts = std::map<std::string, TTF_Font*>();

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

	for (auto font : fonts)
	{
		if (font.second != nullptr) TTF_CloseFont(font.second);
	}
	fonts.clear();
}

Sprite* AssetManager::GetSprite(std::string filename)
{
	std::string fullPath = "Assets/" + filename + ".png";

	if (sprites[fullPath] == nullptr)
	{
		SDL_Surface* pTempSurface = IMG_Load(fullPath.c_str());
		if (pTempSurface == 0) 
		{
			std::cout << " Sprite Not Found 1" << std::endl;
			return nullptr;
		}
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), pTempSurface);
		SDL_FreeSurface(pTempSurface);
		if (pTexture != 0) sprites[fullPath] = new Sprite(pTexture);
		else
		{
			std::cout << "Sprite Not Found 2" << std::endl;
			return nullptr;
		}
	}

	return 	sprites[fullPath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	std::string fullPath = "Assets/" + filename + ".ttf";

	if (fonts[fullPath] == nullptr)
	{
		TTF_Font* font = TTF_OpenFont(fullPath.c_str(), size);
		if (font == 0) return nullptr; else return fonts[fullPath] = font;
	}

	return fonts[fullPath];
}
