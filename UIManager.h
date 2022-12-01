#pragma once

#include "AssetManager.h"
#include "SDLManager.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

class UIManager
{
private:
	static	SDL_Texture* messageTexture;
	static SDL_Rect messageRect;

public:
	UIManager() = delete;
	~UIManager() = delete;

	static void Init();
	static void Clear();
	
	static void DrawMessage(std::string message, int x, int y, int size, SDL_Color color);

	static void Draw();
};

