#include "Timer.h"

#include "SDLManager.h"

float Timer::deltaTime = 0;
float Timer::unscaledDeltaTime = 0;
float Timer::lastTime = 0;
float Timer::timeScale = 1;

int Timer:: startTicks = 0;
int Timer:: pausedTicks = 0;
bool Timer:: paused = false;
bool Timer:: started = false;

void Timer::Init()
{


}

void Timer::Tick()
{
	deltaTime = (SDL_GetTicks() - lastTime) * (FPS / 1000.0f) * timeScale;

	if (deltaTime > Target_DeltaTime) deltaTime = Target_DeltaTime * timeScale;

	unscaledDeltaTime = deltaTime / timeScale;

	lastTime = SDL_GetTicks();
}

void Timer::Start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::Pause()
{
    //If the timer is running and isn't already paused
    if ((started == true) && (paused == false))
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::Unpause()
{
    //If the timer is paused
    if (paused == true)
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::Get_ticks()
{
    //If the timer is running
    if (started == true)
    {
        //If the timer is paused
        if (paused == true)
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::Is_started()
{
    return started;
}

bool Timer::Is_paused()
{
    return paused;
}