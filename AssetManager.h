#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "SpriteRenderer.h"

#include <SDL_image.h>
#include "SDLManager.h"

class AssetManager
{
private:
	static std::map<std::string, Sprite*> sprites;

	static std::map<std::string, TTF_Font*> fonts;
public:

	static void Init();
	static void Clear();
	
	static Sprite* GetSprite(std::string filename);
	
	static TTF_Font* GetFont(std::string filename, int size);

private:
	AssetManager() = delete;
	~AssetManager() = delete;


};

