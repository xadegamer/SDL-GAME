#include "Game.h"
#include "AssetManager.h"
#include "InputManager.h"

#include <iostream>

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
		isRunning = true;
		std::cout << "init success\n";
		isRunning = true; // everything inited successfully, start the main loop

		player = new Player;

		cursor = AssetManager::GetSprite("Cursor");
		
		return true;
	}
	else return false;
}

void Game::Render()
{
	SDL_RenderClear(SDLManager::GetRenderer()); // clear the renderer to the draw color

	player->Render();

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);

	//Render
	
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

void Game::Update()
{
	player->Update();
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(SDLManager::GetWindow());
	SDL_DestroyRenderer(SDLManager::GetRenderer());
	SDL_Quit();
}

void Game::LoadScore()
{
}

void Game::SaveScore(int score)
{
}
