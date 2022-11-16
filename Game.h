#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "SpriteRenderer.h"


class Game
{
private:
	int highscore{};
	int lastScore{};
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool isRunning;

	int currentFrame;

	GameObject newObject;
	Player player;

public:

	Game();

	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Render();
	
	void Update();
	
	void HandleEvents();
	
	void Clean();

	bool IsRunning() { return isRunning; }
	
	void LoadScore();

	void SaveScore(int score);
};

