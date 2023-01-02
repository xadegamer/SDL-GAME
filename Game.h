#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "GroundTileMap.h"
#include "LayoutTileMap.h"

#include "SDLManager.h"
#include "AssetManager.h"
#include "UIManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include <iostream>

struct PlayerData
{
	int totalMoney = 0;
	int numOfLevelUnlocked = 2;
};

enum class GameState
{
	PlayMode, PauseMode, MainMenu, GameOver
};

class Game
{
private:

	bool isRunning;
	bool showDebug;
	int currentMoney;
	int currentLevel;
	int maxLevel;	
	GameState gameState;
	GroundTileMap* groundTileMap;
	LayoutTileMap* layoutTileMap;
	PlayerData playerData;
	
public:

	Game();

	~Game();

	void SetUp();
	
	void Render();
	
	void Update(float deltaTime);
	
	void HandleEvents();
	
	bool IsRunning() { return isRunning; }

	void LoadLevel(int level);
	
	void ResetGame();
	
	void RetryGame();
	
	void Quit();
	
	void ChangeGameState(GameState state);
	
	void PlayGameStateMusic();

	void SetUpWinCondition();
	
	void CheckWinCondition(int enemiesKilled);
	
	void AddMoney(int amount);
	
	void ToggleDebug(bool toggle);
	
	void SaveData();
	
	void LoadData();

	int TotalNumberOfLevelUnlocked();
};

