#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Camera.h"

#include <iostream>



bool Game::isRunning = false;
Player* Game::player = nullptr;
Sprite* Game::cursor = nullptr;
Enemy* Game::enemy = nullptr;
Button* Game::button = nullptr;
Text* Game::text = nullptr;

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

	text = new Text("Test Text", "Vorgang", { 255, 255, 255, 255 }, Vector2(800, 800));

	button = new Button(Vector2(500, 500), Vector2(200, 200), 0);

	button->AddText("Hello World", "Vorgang", { 255, 255, 255, 255 });

	int i = 0;

	button->OnClick = [=]() mutable
	{
		if (i == 0)
		{
			button->text->SetText("New Text");
			i++;
		}
		else if (i == 1)
		{
			button->text->SetText("E");
			i++;
		}
		else if (i == 2)
		{
			button->text->SetText("EEEEEEEEEEEEEEEEEEE");
			i = 0;
		}

		text->SetText("New Text");
		std::cout << button->transform->position << endl;
		std::cout << button->text->transform->position << endl;
	};



	//AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);

	Camera::SetUp(player);
}

void Game::SpawnBullet(Vector2 startPosition, BulletType bulletType, Vector2 direction)
{
	float offsetX = 10;
	float offsetY = -80;
	double theta = player->transform->rotation * (M_PI / 180);
	Vector2 spawnPos = Vector2(startPosition.x + offsetX * cos(theta) - offsetY * sin(theta), startPosition.y + offsetX * sin(theta) + offsetY * cos(theta));
	Bullet* bullet = new Bullet(spawnPos, bulletType, direction);
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

	//check collision between all game objects with colliders

	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		Collider* colliderA = nullptr;
		if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<Collider>(colliderA))
		{
			for (int j = 0; j < GameObject::GetActiveGameobjects().size(); j++)
			{
				Collider* colliderB = nullptr;		
				if (GameObject::GetActiveGameobjects()[j]->TryGetComponent<Collider>(colliderB))
				{
					if (colliderA != colliderB)
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

	if(button) button->Update();

	if (text) text->Update();

	Camera::Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 255, 255);

	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	for (auto& gameObject : GameObject::GetActiveGameobjects()) gameObject->Draw();

	UIManager::Draw();

	if (button) button->Draw();
	if (text) text->Draw();

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

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);
	
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