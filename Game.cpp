#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include "UIManager.h"

#include "Enemy.h"

#include <iostream>

#include "Engine.h"

Game::Game()
{
	isRunning = false;
	showDebug = false;
	gameState = GameState::MainMenu;
	groundTileMap = nullptr;
	money = 0;
	layoutTileMap = nullptr;

	srand((unsigned)time(NULL));
	UIManager::Init();
	isRunning = true; // everything inited successfully, start the main loop
	PlayGameStateMusic();
}

Game::~Game()
{
	std::cout << "cleaning game\n";
	UIManager::Clean();
	Camera::Clean();
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}

void Game::LoadLevel()
{
	groundTileMap = new GroundTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Ground Map 1.txt");
	layoutTileMap = new LayoutTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map 1.txt");

	Enemy::GetOnAnyEnemyKilled() = [this](int num){ CheckWinCondition(num); };

	Camera::SetUp(GameObject::FindGameObjectWithTag(Tag::PLAYER));

	AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
}

void Game::StartGame()
{
	LoadLevel();
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
	StartGame();
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
	case GameState::PlayMode:
		AudioManager::ResumeMusic();
		break;
	case GameState::PauseMode:
		AudioManager::PauseMusic();
		break;
	case GameState::MainMenu:
		AudioManager::PlayMusic(AssetManager::GetMusic("Western Spaghetti - Chris Haugen"), true);
		break;
	case GameState::GameOver:
		AudioManager::PlayMusic(AssetManager::GetMusic("Don't Ya Bite Now - Dan Lebowitz"), true);
		break;
		
	default:break;
	}
}

void Game::CheckWinCondition(int enemiesKilled)
{
	if (gameState == GameState::PlayMode && enemiesKilled == 0)
	{
		ChangeGameState(GameState::GameOver);
		UIManager::EnableCanvasByID("WinMenu");
	}
}

void Game::AddMoney(int amount)
{
	money += amount;
	std::to_string(money);
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("MoneyText")->SetText("Money: " + std::to_string(money));
}

void Game::ToggleDebug(bool toggle)
{
	showDebug = toggle;
}

void Game::SaveData(int score)
{
	std::ofstream file;
	file.open("data.txt");
	if (!file.bad())
	{
		file << score;
		file.close();
	}
}

void Game::LoadData()
{
	int highScore;
	
	std::ifstream file;
	file.open("data.txt");
	if (!file.bad())
	{
		file >> highScore;
		file.close();
	}
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