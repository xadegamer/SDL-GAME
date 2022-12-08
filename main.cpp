#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "InputManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Game.h"


using namespace std;

#define PI 3.14159265358979323846

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int arg, char* argv[])
{
	Uint32 frameStart, frameTime;
	Sint32 delaytime;
	float moveSpeed = 3.0f;
	
	Game* g_game = new Game();

	g_game->Init("Chapter 1", 100, 100, 1280, 720, false);


	while (g_game->IsRunning())
	{
		frameStart = SDL_GetTicks();
		
		InputManager::Update();
		
		g_game->HandleEvents();
		g_game->Update();
		g_game->Render();
		

		InputManager::UpdatePreviousInput();

		//frameTime = SDL_GetTicks() - frameStart;
		//if (frameTime < DELAY_TIME) SDL_Delay((int)(DELAY_TIME - frameTime));

		delaytime = DELAY_TIME - (SDL_GetTicks() - frameStart);
		if (delaytime > 0) SDL_Delay((int)delaytime);
		frameStart = SDL_GetTicks();
	}

	g_game->Clean();

	
//	OldMain(arg, argv);
		
	return 0;
}
