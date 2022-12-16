#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include <iostream>

bool Game::isRunning = false;
Player* Game::player = nullptr;
Sprite* Game::cursor = nullptr;
bool Game::showDebug = false;
GameState Game::gameState = GameState::MainMenu;

TileMap* Game::tileMap = nullptr;

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
	tileMap = new TileMap((LEVEL_WIDTH / 89) + 1,( LEVEL_HEIGHT/ 89) + 1, 89);
	
	Vector2 playerPos = tileMap->GetTilePositionById("P");
	std::cout << "Player pos: " << playerPos.x << ", " << playerPos.y << std::endl;
	player = GameObject::Instantiate(new Player(playerPos,100));

	Camera::SetUp(player);

	GameObject::Instantiate(new Enemy(Vector2(600, 200),100));

	GameObject::Instantiate(new HealthKit(playerPos - Vector2(100, 100), "HeathKit", ColliderType::BOX,1, 50));

	//GameObject::InstantiateRandomPositionOnScreen(new Enemy(100));
	
	//prop = GameObject::Instantiate(new GasCylinder(Vector2(300, 300),"BarrelSmall", ColliderType::CIRCLE,1, true, false));
	//
	//prop = GameObject::Instantiate(new GasCylinder(Vector2(400, 300), "BarrelSmall", ColliderType::CIRCLE, 1, true, false));

	//prop = GameObject::Instantiate(new GasCylinder(Vector2(500, 300), "BarrelSmall", ColliderType::CIRCLE, 1, true, false));

	//prop = GameObject::Instantiate(new GasCylinder(Vector2(600, 300), "BarrelSmall", ColliderType::CIRCLE, 1, true, false));

	GameObject::Instantiate(new Prop(Vector2(700, 300), "Tree_3", ColliderType::None,3, true, false));

	GameObject::Instantiate(new Prop(Vector2(900, 500), "Car_1", ColliderType::BOX, 2, true, false));
	
	AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
}

void Game::HandleCollision()
{
	//check collision between all game objects with colliders
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* colliderA = nullptr;
		if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed() && GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(colliderA))
		{
			for (int j = 0; j < GameObject::GetActiveGameobjects().size(); j++)
			{
				Collider* colliderB = nullptr;
				if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed() && GameObject::GetActiveGameobjects()[j]->TryGetComponent<Collider>(colliderB))
				{
					if (colliderA != colliderB && colliderA->GetIsEnabled() && colliderB->GetIsEnabled())
					{
						if (CollisionManager::CheckCollision(colliderA, colliderB))
						{
							if (colliderA == nullptr || colliderB == nullptr || !colliderA->GetIsEnabled() || !colliderB->GetIsEnabled()) continue;
							colliderA->OnCollision(colliderB);
							if (colliderA == nullptr || colliderB == nullptr || !colliderA->GetIsEnabled() || !colliderB->GetIsEnabled()) continue;
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
	delete tileMap;
	tileMap = nullptr;
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
		
		break;
	case GameState::PauseMode:
		
		break;
	case GameState::MainMenu:
		AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
		break;
	case GameState::GameOver:
		break;
		
	default:break;
	}
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
		if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed() && GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(collider))
		{
			if (collider->GetIsEnabled()) collider->Draw();
		}
	}

	// draw only object with colliders
	//for (auto& gameObject : GameObject::GetActiveGameobjects())
	//{
	//	SpriteRenderer* spriteRen = gameObject->GetComponent<SpriteRenderer>();
	//	if (spriteRen) gameObject->GetComponent<SpriteRenderer>()->DebugRect();
	//}
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
			if(!GameObject::GetActiveGameobjects()[i]->IsDestroyed()) GameObject::GetActiveGameobjects()[i]->Update(deltaTime);
		}

		HandleCollision();

		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed()) GameObject::GetActiveGameobjects()[i]->LateUpdate(deltaTime);
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
		tileMap->DrawMap();
		
		// loop throught all game objects and render them according to spriterenderer sorting order
		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 1)
				if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}

		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 2)
				if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
		}


		for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
		{
			SpriteRenderer* spriteRenderer = nullptr;
			if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<SpriteRenderer>(spriteRenderer) && spriteRenderer->GetSortingOrder() == 3)
				if (!GameObject::GetActiveGameobjects()[i]->IsDestroyed()) GameObject::GetActiveGameobjects()[i]->Draw();
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