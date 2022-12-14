#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h""
#include "Prop.h"

#include "SDLManager.h"
#include "AssetManager.h"
#include "UIManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include <iostream>

//The dimensions of the level
const int LEVEL_WIDTH = 1280 * 1.2;
const int LEVEL_HEIGHT = 960 * 1.2;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

class Game
{
private:

	static bool isRunning;

public:
	
	static Player* player;
	static Sprite* cursor;
	static Enemy* enemy;
	static Prop* prop;
	
public:

	Game();

	~Game();

	static bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	static void Render();
	
	static void Update(float deltaTime);
	
	static void HandleEvents();
	
	static void Clean();

	static bool IsRunning() { return isRunning; }

	static void SpawnGameObjects();

	static void Quit();
	
	static void Debug();
};

