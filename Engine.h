#pragma once
#include <iostream>
#include <vector>

#include "SDLManager.h"
#include "InputManager.h"
#include "Game.h"
#include "TimeManager.h"

const int SCREEN_TICK_PER_FRAME = 16;
const float ANIMATION_INTERVAL = 0.05;

class Engine
{
private:
	Engine() = delete;
	~Engine() = delete;
	static void FrameCap();
	
public:
	
	static TimeManager systemTimer;
	static TimeManager deltaTimer;
	static int countedFrames;
	static void Start();
};

