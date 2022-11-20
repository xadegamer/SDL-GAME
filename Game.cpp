#include "Game.h"

#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	
	std::cout << "init success\n";
	isRunning = true; // everything inited successfully, start the main loop

	player.AddComponent<SpriteRenderer>()->Load("Assets/Character.png", "Player", m_pRenderer);
	
	return true;
}

void Game::Render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	player.Render(m_pRenderer);
	//Render
	
	SDL_RenderPresent(m_pRenderer); // draw to the screen
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
	player.Update();
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::LoadScore()
{
}

void Game::SaveScore(int score)
{
}
