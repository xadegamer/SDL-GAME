#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteRenderer.h"

#include "SDLManager.h"
#include "AssetManager.h"
#include "UIManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include <iostream>

class Game
{
private:
	int highscore{};
	int lastScore{};
	bool isRunning;

	int currentFrame;

public:
	GameObject newObject;
	Player* player;
	Sprite* cursor;

	Enemy* enemy;
	
public:

	Game();

	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Render();
	
	void Update(float deltaTime);
	
	void HandleEvents();
	
	void Clean();

	bool IsRunning() { return isRunning; }
	
	void LoadScore();

	void SaveScore(int score);
};

