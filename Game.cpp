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

void Game::SpawnGameObjects()
{
	groundTileMap = new GroundTileMap((LEVEL_WIDTH / 89) + 1, (LEVEL_HEIGHT / 89) + 1, 89, "Assets/Maps/Ground Map 1.txt");
	layoutTileMap = new LayoutTileMap((LEVEL_WIDTH / 89) + 1, (LEVEL_HEIGHT / 89) + 1, 89, "Assets/Maps/Layout Map 1.txt");

	Enemy::OnAnyEnemyKilled = Game::CheckWinCondition;
	
	player = GameObject::Instantiate(new Player(layoutTileMap->GetPlayerPosition(),100));

	Camera::SetUp(player);
	
	AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
}

void Game::HandleCollision()
{
	// check collision between object using layermasks
	
	//check collision between all game objects with colliders
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* colliderA = nullptr;
		if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed() && GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(colliderA))
		{
			for (int j = 0; j < GameObject::GetActiveGameobjects().size(); j++)
			{
				Collider* colliderB = nullptr;
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed() && GameObject::GetActiveGameobjects()[j]->TryGetComponent<Collider>(colliderB))
				{					
					if (colliderA != colliderB && colliderA->GetIsEnabled() && colliderB->GetIsEnabled())
					{
						if (CollisionManager::CheckCollision(colliderA, colliderB))
						{
							colliderA->OnCollision(colliderB);
							colliderB->OnCollision(colliderA);
						}
					}
				}
			}
		}
	}
}

void Game::StartGame()
{
	SpawnGameObjects();
	ChangeGameState(GameState::PlayMode);
}

void Game::ResetGame()
{
	delete groundTileMap;
	groundTileMap = nullptr;
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
		AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
		break;
	case GameState::PauseMode:
		
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
	if (enemiesKilled == 0)
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

void Game::Debug()
{
	// draw only object with colliders

	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* collider = nullptr;
		if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed() && GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(collider))
		{
			if (collider->GetIsEnabled()) collider->Draw();
		}
	}

	// draw only object with colliders
	for (auto& gameObject : GameObject::GetActiveGameobjects())
	{
		SpriteRenderer* spriteRen = gameObject->GetComponent<SpriteRenderer>();
		if (spriteRen) gameObject->GetComponent<SpriteRenderer>()->DebugRect();
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
		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			GameObject::GetActiveGameobjects()[i]->Update(deltaTime);
		}

		HandleCollision();

		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			 GameObject::GetActiveGameobjects()[i]->LateUpdate(deltaTime);
		}

		Camera::Update();
	}

	UIManager::Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 255, 255);

	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	if (gameState == GameState::PlayMode)
	{
		groundTileMap->DrawMap();

		// loop throught all game objects and render them according to spriterenderer sorting order
		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 0)
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}
		
		// loop throught all game objects and render them according to spriterenderer sorting order
		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 1)
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}

		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 2)
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}


		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 3)
				if (!GameObject::GetActiveGameobjects()[i]->IsToBeDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}

		if(showDebug) Debug();
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