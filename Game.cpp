#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include "UIManager.h"

#include "Enemy.h"

#include <iostream>

bool Game::isRunning = false;
Player* Game::player = nullptr;
Sprite* Game::cursor = nullptr;
bool Game::showDebug = false;
GameState Game::gameState = GameState::MainMenu;
GroundTileMap* Game::groundTileMap = nullptr;
int Game::money = 0;
LayoutTileMap* Game::layoutTileMap = nullptr;

Game::Game()
{
	
}

Game::~Game()
{
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDLManager::Init(title, xpos, ypos, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen))
	{	
		srand((unsigned)time(NULL));
		UIManager::Init();
		cursor = AssetManager::GetSprite("cursor");
		std::cout << "init success\n";
		isRunning = true; // everything inited successfully, start the main loop
		PlayGameStateMusic();
		return true;
	}
	else return false;
}

void Game::LoadLevel()
{
	groundTileMap = new GroundTileMap((LEVEL_WIDTH / TILE_SIZE) + 1, (LEVEL_HEIGHT / TILE_SIZE) + 1, TILE_SIZE, "Assets/Maps/Ground Map 1.txt");
	layoutTileMap = new LayoutTileMap((LEVEL_WIDTH / TILE_SIZE) + 1, (LEVEL_HEIGHT / TILE_SIZE) + 1, TILE_SIZE, "Assets/Maps/Layout Map 1.txt");

	Enemy::GetOnAnyEnemyKilled() = Game::CheckWinCondition;
	
	player = GameObject::Instantiate(new Player(layoutTileMap->GetPlayerPosition(),100));

	Camera::SetUp(player);

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
	SDL_RenderClear(SDLManager::GetRenderer());

	if (gameState == GameState::PlayMode)
	{
		groundTileMap->DrawMap();

		GameObject::DrawAllActive();
	
		if (showDebug) GameObject::ShowAllDebugVisuals();
	}
	
	UIManager::Draw();
		
	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);
	
	SDL_RenderPresent(SDLManager::GetRenderer()); // draw to the screen
}

void Game::Clean()
{
	std::cout << "cleaning game\n";

	UIManager::Clean();
	Camera::Clean();
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}