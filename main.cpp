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
#include "TimeManager.h"

using namespace std;

TimeManager systemTimer;
TimeManager deltaTimer;
int countedFrames = 0;
const int SCREEN_TICK_PER_FRAME = 16;
const float ANIMATION_INTERVAL = 0.05;

void FrameCap()
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

	g_game->SpawnGameObjects();

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

		FrameCap();
	}

	g_game->Clean();

	return 0;
}