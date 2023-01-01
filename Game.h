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



enum class GameState
{
	PlayMode, PauseMode, MainMenu, GameOver
};

class Game
{
private:

	bool isRunning;
	bool showDebug;
	int totalMoney;
	int currentMoney;
	GameState gameState;
	GroundTileMap* groundTileMap;
	LayoutTileMap* layoutTileMap;
	
public:

	Game();

	~Game();
	
	 void Render();
	
	 void Update(float deltaTime);
	
	 void HandleEvents();
	
	 bool IsRunning() { return isRunning; }
	
	 void LoadLevel();
	
	 void StartGame();
	
	 void ResetGame();
	
	 void RetryGame();
	
	 void Quit();
	
	 void ChangeGameState(GameState state);
	
	 void PlayGameStateMusic();
	
	 void CheckWinCondition(int enemiesKilled);
	
	 void AddMoney(int amount);
	
	 void ToggleDebug(bool toggle);
	
	 void SaveData(int score);
	
	 void LoadData();
};

