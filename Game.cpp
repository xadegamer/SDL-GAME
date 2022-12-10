#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

Game::Game()
{
	
}

Game::~Game()
{
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	if (SDLManager::Init(title, xpos, ypos, width, height, fullscreen))
	{	
		AssetManager::Init();
		InputManager::Init();
		UIManager::Init();		
		std::cout << "init success\n";
		isRunning = true; // everything inited successfully, start the main loop
		return true;
	}
	else return false;
}

void Game::SpawnGameObjects()
{
	player = new Player;
	gameObjects.push_back(player);

	enemy = new Enemy(Vector2(100, 100));
	gameObjects.push_back(enemy);

	cursor = AssetManager::GetSprite("cursor");

	//AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);

	Camera::SetUp(player);
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

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		if (bullet)
		{	
			gameObjects.erase(find(gameObjects.begin(), gameObjects.end(), bullet));
			delete bullet;
			bullet = nullptr;		
		}
		
		bullet = new Bullet(player->GetComponent<Collider>()->GetPosition() , BulletType::PLAYER);
		gameObjects.push_back(bullet);
	}
}

void Game::Update(float deltaTime)
{
	for (auto& gameObject : gameObjects) gameObject->Update(deltaTime);

	//update all game objects with colliders
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetComponent<Collider>()) gameObject->GetComponent<Collider>()->Update(Vector2(Camera::GetPosition()));
	}
	
	for (int i = 0; i < gameObjects.size(); i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (CollisionManager::CheckCollision(gameObjects[i]->GetComponent<Collider>(), gameObjects[j]->GetComponent<Collider>()))
			{
				gameObjects[i]->GetComponent<Collider>()->OnCollision(gameObjects[j]->GetComponent<Collider>());
				gameObjects[j]->GetComponent<Collider>()->OnCollision(gameObjects[i]->GetComponent<Collider>());
			}
		}
	}

	Camera::Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 255, 255);

	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	for (auto& gameObject : gameObjects) gameObject->Draw(Camera::GetPosition());

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);

	UIManager::Draw();

	// draw only object with colliders
	for (auto& gameObject : gameObjects)
	{
		Collider* collider = gameObject->GetComponent<Collider>();
		if (collider) gameObject->GetComponent<Collider>()->Draw();
	}

	// draw only object with colliders
	for (auto& gameObject : gameObjects)
	{
		SpriteRenderer* spriteRen = gameObject->GetComponent<SpriteRenderer>();
		if (spriteRen) gameObject->GetComponent<SpriteRenderer>()->DebugRect();
	}


	SDL_RenderPresent(SDLManager::GetRenderer()); // draw to the screen
}

void Game::Clean()
{
	std::cout << "cleaning game\n";

	Camera::Clean();
	for (auto& gameObject : gameObjects) delete gameObject;
	AssetManager::Clear();
	SDLManager::Clean();
}

void Game::LoadScore()
{
}

void Game::SaveScore(int score)
{
}
