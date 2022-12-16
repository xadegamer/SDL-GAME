#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h""
#include "Prop.h"
#include "GasCylinder.h"
#include "TileMap.h"
#include "HealthKit.h"

#include "SDLManager.h"
#include "AssetManager.h"
#include "UIManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include <iostream>

//The dimensions of the level
const int LEVEL_WIDTH = 2560;
const int LEVEL_HEIGHT = 1920;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

enum class GameState
{
	PlayMode, PauseMode, MainMenu, GameOver
};

class Game
{
private:

	static bool isRunning;
	static bool showDebug;

public:
	
	static GameState gameState;
	static Player* player;
	static Sprite* cursor;
	static TileMap* tileMap;
	
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

	static void HandleCollision();
	
	static void StartGame();

	static void ResetGame();

	static void RetryGame();

	static void Quit();
	
	static void ChangeGameState(GameState state);

	static void PlayGameStateMusic();

	static void ToggleDebug(bool toggle);

	static void SaveData(int score);

	static void LoadData();

	static void Debug();
};

