#pragma once
#include "SDL.h"

class SDLManager
{
private:
	
	static SDL_Window* m_pWindow;
	static SDL_Renderer* m_pRenderer;
	
public:

	static bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	static SDL_Window* GetWindow() { return m_pWindow; }
	static SDL_Renderer* GetRenderer() { return m_pRenderer; }

	static void SetCursorVisibility(bool show);
	
	static void CursorBlit(SDL_Texture* texture, int x, int y, bool center);
};

