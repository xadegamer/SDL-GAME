#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

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
		
		isRunning = true;
		
		std::cout << "init success\n";
		isRunning = true; // everything inited successfully, start the main loop

		player = new Player;

		enemy = new Enemy(Vector2(50, 50));

		cursor = AssetManager::GetSprite("Cursor");

		AudioManager::PlayMusic(AssetManager::GetMusic("Three Kinds of Suns - Norma Rockwell"), true);
		
		return true;
	}
	else return false;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255, 255, 255, 255);
	
	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	player->Draw();

	enemy->Draw();

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);

	UIManager::Draw();
	
	player->GetComponent<Collider>()->Draw();

	enemy->GetComponent<Collider>()->Draw();

	SDL_RenderPresent(SDLManager::GetRenderer()); // draw to the screen
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void Game::Update(float deltaTime)
{
	player->Update(deltaTime);

	enemy->Update(deltaTime);

	if (CollisionManager::CheckCollision(player->GetComponent<Collider>(), enemy->GetComponent<Collider>()))
	{
		std::cout << "Collision!\n";
	}
}

void Game::Clean()
{
	std::cout << "cleaning game\n";

	AssetManager::Clear();
	SDLManager::Clean();
}

void Game::LoadScore()
{
}

void Game::SaveScore(int score)
{
}
