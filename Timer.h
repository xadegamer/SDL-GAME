#pragma once

const int FPS = 60;
const float Target_DeltaTime = 1.5f;

class Timer
{
private:

	Timer() = delete;
	~Timer() = delete;

public:

	static float deltaTime;
	static float unscaledDeltaTime;

	static float lastTime;

	static float timeScale;

	static void Init();
	static void Tick();

private:
    //The clock time when the timer started
    static int startTicks;

    //The ticks stored when the timer was paused
    static int pausedTicks;

    //The timer status
    static bool paused;
    static bool started;

public:
	
    //The various clock actions
    static void Start();
    static void Stop();
    static void Pause();
    static void Unpause();

    //Gets the timer's time
    static int Get_ticks();

    //Checks the status of the timer
    static bool Is_started();
    static bool Is_paused();
};

