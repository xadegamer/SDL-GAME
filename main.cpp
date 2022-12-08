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
#include "Timer.h"
#include "TimeManager.h"

using namespace std;

TimeManager systemTimer;
TimeManager deltaTimer;
int countedFrames = 0;
const int SCREEN_TICK_PER_FRAME = 16;
const float ANIMATION_INTERVAL = 0.05;

void frameCap()
{
	//Calculate and correct fps
	float avgFPS = countedFrames / (systemTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	++countedFrames;

	//If frame finished early
	int frameTicks = deltaTimer.getTicks();
	if (frameTicks < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
	}
}

int main(int arg, char* argv[])
{
	float moveSpeed = 3.0f;

	Game* g_game = new Game();

	g_game->Init("Chapter 1", 100, 100, 1280, 720, false);

	float timer = 0;

	systemTimer.tick();
	deltaTimer.tick();

	while (g_game->IsRunning())
	{
		deltaTimer.tick();

		//if (timer >= 3)
		//{
		//	std::cout << "deltaTime: " << deltaTimer.getDeltaTime() << std::endl;
		//	timer = 0;
		//}
		//else timer += deltaTimer.getDeltaTime();

		InputManager::Update();

		g_game->HandleEvents();
		g_game->Update(deltaTimer.getDeltaTime());
		g_game->Render();

		InputManager::UpdatePreviousInput();

		frameCap();
	}

	g_game->Clean();

	return 0;
}



//#define PI 3.14159265358979323846
//
//const int DELAY_TIME = 1000.0f / FPS;
//
//int main(int arg, char* argv[])
//{
//	Uint32 frameStart, frameTime;
//	Sint32 delaytime;
//	float moveSpeed = 3.0f;
//	
//	Game* g_game = new Game();
//
//	g_game->Init("Chapter 1", 100, 100, 1280, 720, false);
//
//	float timer = 0;
//
//	while (g_game->IsRunning())
//	{
//		frameStart = SDL_GetTicks();
//		
//		Timer::Tick();
//		
//		if (timer >= 5)
//		{
//			std::cout << "deltaTime: " << Timer::deltaTime << std::endl;
//			timer = 0;
//		}
//		else
//		{
//			timer += Timer::deltaTime;
//		}
//		
//		InputManager::Update();
//		
//
//		
//		g_game->HandleEvents();
//		g_game->Update();
//		g_game->Render();
//		
//
//		InputManager::UpdatePreviousInput();
//
//		//frameTime = SDL_GetTicks() - frameStart;
//		//if (frameTime < DELAY_TIME) SDL_Delay((int)(DELAY_TIME - frameTime));
//
//		delaytime = DELAY_TIME - (SDL_GetTicks() - frameStart);
//		if (delaytime > 0) SDL_Delay((int)delaytime);
//		frameStart = SDL_GetTicks();
//	}
//
//	g_game->Clean();
//		
//	return 0;
//}
