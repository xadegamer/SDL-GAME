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
	totalMoney = 0;
	currentMoney = 0;
	layoutTileMap = nullptr;
	srand((unsigned)time(NULL));
	UIManager::Init();
	DialogManager::Init();
	LoadData();
	isRunning = true; // everything inited successfully, start the main loop
	PlayGameStateMusic();
}

Game::~Game()
{
	std::cout << "cleaning game\n";
	UIManager::Clean();
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}

void Game::LoadLevel()
{
	int randomLevel = MathUtility::RandomRange(1, 2);
	//groundTileMap = new GroundTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Ground Map 1.txt");
	//layoutTileMap = new LayoutTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map " + std::to_string(randomLevel) + ".txt");

	groundTileMap = new GroundTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Ground Map 2.txt");
	layoutTileMap = new LayoutTileMap((Engine::LEVEL_WIDTH / Engine::TILE_SIZE) + 1, (Engine::LEVEL_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map 2.txt");
	
	Enemy::GetOnAnyEnemyKilled() = [this](int num){ CheckWinCondition(num); };

	Camera::SetUp(GameObject::FindGameObjectWithTag(Tag::PLAYER));

	AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);

	DialogManager::ShowDialog("Intro");
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
		case GameState::PlayMode:AudioManager::ResumeMusic(); break;
		case GameState::PauseMode:AudioManager::PauseMusic(); break;
		case GameState::MainMenu: AudioManager::PlayMusic(AssetManager::GetMusic("Western Spaghetti - Chris Haugen"), true); break;
		case GameState::GameOver:AudioManager::PlayMusic(AssetManager::GetMusic("Don't Ya Bite Now - Dan Lebowitz"), true);	break;	
		default:break;
	}
}

void Game::CheckWinCondition(int enemiesKilled)
{
	if (isRunning && (gameState == GameState::PlayMode && enemiesKilled == 0))
	{
		totalMoney += currentMoney;
		SaveData(totalMoney);
		UIManager::GetCanvasByID("MainMenu")->GetUIObjectByID<Text>("MenuMoneyText")->SetText(std::to_string(totalMoney));
		
		currentMoney = 0;
		UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("MoneyText")->SetText("Money: " + std::to_string(currentMoney));
		
		ChangeGameState(GameState::GameOver);
		UIManager::EnableCanvasByID("WinMenu");
	}
}

void Game::AddMoney(int amount)
{
	currentMoney += amount;
	std::to_string(currentMoney);
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Text>("MoneyText")->SetText("Money: " + std::to_string(currentMoney));
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
	std::ifstream file;
	file.open("data.txt");
	if (!file.bad())
	{
		file >> totalMoney;
		file.close();
	}
	UIManager::GetCanvasByID("MainMenu")->GetUIObjectByID<Text>("MenuMoneyText")->SetText(std::to_string(totalMoney));
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