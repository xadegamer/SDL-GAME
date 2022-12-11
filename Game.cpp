#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include <iostream>

bool Game::isRunning = false;
Player* Game::player = nullptr;
Sprite* Game::cursor = nullptr;
Enemy* Game::enemy = nullptr;

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

	enemy = new Enemy(Vector2(100, 100));

	cursor = AssetManager::GetSprite("cursor");

	//AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);

	Camera::SetUp(player);
}

void Game::SpawnBullet(Vector2 startPosition, BulletType bulletType, Vector2 direction)
{
	Bullet* bullet = new Bullet(startPosition, bulletType, direction);
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
	//update all game objects with colliders
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		GameObject::GetActiveGameobjects()[i]->Update(deltaTime);
	}

	//update all game objects with colliders
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* collider = nullptr;
		if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(collider)) collider->Update();
	}
	
	Collider* colliderA;
	Collider* colliderB;
	
	//check collision between all game objects with colliders
	
	
	
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		for (int j = i + 1; j < GameObject::GetActiveGameobjects().size(); j++)
		{
			if (CollisionManager::CheckCollision(GameObject::GetActiveGameobjects()[i]->GetComponent<Collider>(), GameObject::GetActiveGameobjects()[j]->GetComponent<Collider>()))
			{
				GameObject::GetActiveGameobjects()[i]->GetComponent<Collider>()->OnCollision(GameObject::GetActiveGameobjects()[j]->GetComponent<Collider>());
				GameObject::GetActiveGameobjects()[j]->GetComponent<Collider>()->OnCollision(GameObject::GetActiveGameobjects()[i]->GetComponent<Collider>());
			}
		}
	}

	Camera::Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 255, 255);

	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	for (auto& gameObject : GameObject::GetActiveGameobjects()) gameObject->Draw();

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);

	UIManager::Draw();

	// draw only object with colliders
	for (auto& gameObject : GameObject::GetActiveGameobjects())
	{
		Collider* collider = gameObject->GetComponent<Collider>();
		if (collider) gameObject->GetComponent<Collider>()->Draw();
	}

	// draw only object with colliders
	for (auto& gameObject : GameObject::GetActiveGameobjects())
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
	GameObject::DestroyAllGameObjects();
	AssetManager::Clear();
	SDLManager::Clean();
}