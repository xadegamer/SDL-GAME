#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include "UIManager.h"

#include "DialogManager.h"

#include "Enemy.h"

#include <iostream>

#include "Engine.h"

Game::Game()
{
	isRunning = false;
	showDebug = false;
	gameState = GameState::MainMenu;
	groundTileMap = nullptr;
	currentMoney = 0;
	layoutTileMap = nullptr;
	playerData = PlayerData();
}

Game::~Game()
{
	std::cout << "cleaning game\n";
	UIManager::Clean();
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}

void Game::SetUp()
{
	srand((unsigned)time(NULL));
	LoadData();
	UIManager::Init();
	DialogManager::Init();
	UIManager::GetCanvasByID("MainMenu")->GetUIObjectByID<Text>("MenuMoneyText")->SetText(std::to_string(playerData.totalMoney));
	isRunning = true; // everything inited successfully, start the main loop
	PlayGameStateMusic();
}

void Game::LoadLevel(int level)
{
	// Loads the level from the file and sets up the game
	
	currentLevel = level;
	
	groundTileMap = new GroundTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Ground Map " + std::to_string(level) + ".txt");
	layoutTileMap = new LayoutTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map " + std::to_string(level) + ".txt");
	
	SetUpWinCondition();
	
	Camera::SetUp(GameObject::FindGameObjectWithTag(Tag::PLAYER));
	
	AudioManager::PlayMusic(AssetManager::GetMusic("Level " + std::to_string(level)), true);
	
	DialogManager::ShowDialog("Dialog " + std::to_string(level), [this]() {   std::cout << "Dialog finished" << std::endl; });
	
	ChangeGameState(GameState::PlayMode);
}

void Game::ResetGame()
{
	TileMap::Clear();
	GameObject::DestroyAllGameObjects();
}

void Game::RetryGame()
{
	ResetGame();
	LoadLevel(currentLevel);
}

void Game::Quit()
{
	isRunning = false;
}

void Game::ChangeGameState(GameState state)
{
	gameState = state;
	if (gameState == GameState::MainMenu)ResetGame();
	PlayGameStateMusic();
}

void Game::PlayGameStateMusic()
{
	switch (gameState)
	{
		case GameState::PlayMode:AudioManager::ResumeMusic(); break;
		case GameState::PauseMode:AudioManager::PauseMusic(); break;
		case GameState::MainMenu: AudioManager::PlayMusic(AssetManager::GetMusic("Western Spaghetti - Chris Haugen"), true); break;
		case GameState::GameOver:AudioManager::PlayMusic(AssetManager::GetMusic("Don't Ya Bite Now - Dan Lebowitz"), true);	break;	
		default:break;
	}
}

void Game::SetUpWinCondition()
{
	Enemy::GetOnAnyEnemyKilled() = [this](int amount)
	{
		UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("KillCountText")->SetText(std::to_string(amount));
		if (amount == 0) DialogManager::ShowDialog("Success");
	};

	Enemy::GetOnAnyEnemyDespawned() = [this](int num) { CheckWinCondition(num); };
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("KillCountText")->SetText(std::to_string(Enemy::GetNumberOfEnemyAlive()));
}

void Game::CheckWinCondition(int enemiesKilled)
{
	if (isRunning && (gameState == GameState::PlayMode && enemiesKilled == 0))
	{
		playerData.totalMoney += currentMoney;
		SaveData();
		UIManager::GetCanvasByID("MainMenu")->GetUIObjectByID<Text>("MenuMoneyText")->SetText(std::to_string(playerData.totalMoney));

		currentMoney = 0;
		UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("MoneyText")->SetText(std::to_string(currentMoney));

		ChangeGameState(GameState::GameOver);
		UIManager::EnableCanvasByID("WinMenu");
	}
}

void Game::AddMoney(int amount)
{
	currentMoney += amount;
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("MoneyText")->SetText(std::to_string(currentMoney));
}

void Game::ToggleDebug(bool toggle)
{
	showDebug = toggle;
}

void Game::SaveData()
{
	ofstream savedFile("data.txt");
	if (!savedFile.bad()) savedFile << playerData.totalMoney << std::endl << playerData.numOfLevelUnlocked;
}

void Game::LoadData()
{	
	ifstream savedFile("data.txt");
	if (!savedFile.bad()) savedFile >> playerData.totalMoney >> playerData.numOfLevelUnlocked;
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:	isRunning = false;break;
			default:break;
		}
	}
}

void Game::Update(float deltaTime)
{
	if (gameState == GameState::PlayMode)
	{
		GameObject::UpdateAllActive(deltaTime);

		CollisionManager::HandleAllCollision();

		GameObject::LateUpdateAllActive(deltaTime);

		DialogManager::Update(deltaTime);

		Camera::Update();
	}
	
	UIManager::Update(deltaTime);
}

void Game::Render()
{
	if (gameState == GameState::PlayMode)
	{
		groundTileMap->DrawMap();

		GameObject::DrawAllActive();
	
		if (showDebug) GameObject::ShowAllDebugVisuals();
	}
	
	UIManager::Draw();
}

int Game::TotalNumberOfLevelUnlocked()
{
	return playerData.numOfLevelUnlocked;
}