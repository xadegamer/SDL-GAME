#include "Engine.h"


TimeManager Engine::systemTimer;
TimeManager Engine::deltaTimer;
int Engine::countedFrames = 0;

void Engine::Start()
{
	AssetManager::Init();
	InputManager::Init();
	
	Game::Init("Chapter 1", 100, 100, 1280, 720, false);

	systemTimer.tick();
	deltaTimer.tick();

	while (Game::IsRunning())
	{
		deltaTimer.tick();
		
		InputManager::Update();

		Game::HandleEvents();
		Game::Update(deltaTimer.getDeltaTime());
		Game::Render();

		InputManager::UpdatePreviousInput();

		FrameCap();
	}

	AssetManager::Clear();
	Game::Clean();

}

void Engine::FrameCap()
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
	std::string title = "Wild West Ranged [avg fps: " + std::to_string(int(avgFPS)) + "] ";
	SDL_SetWindowTitle(SDLManager::GetWindow(), title.c_str());
}