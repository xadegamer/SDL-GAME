#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "AudioManager.h"
#include "AssetManager.h"

#include "Canvas.h"
#include "Button.h"
#include "Text.h"
#include "Canvas.h"
#include "Slider.h"
#include "ToggleButton.h"
#include "Image.h"
#include "AnimatedImage.h"

class Game;

class UIManager
{
private:
	UIManager() = delete;
	~UIManager() = delete;
	
	static float refreshRate;
	static float currrentRefreshRate;
	
	static Canvas* lastActiveCanvas;
	static Canvas* activeCanvas;

public:

	static std::vector<Canvas*> activeCanvases;
	
	static void Init();
	
	static void SetUpMainMenuCanvas();
	
	static void SetUpOptionCanvas();

	static void SetUpGameCanvas();

	static void SetUpPauseCanvas();

	static void SetUpWinCanvas();

	static void SetUpGameOverCanvas();
	
	static void Draw();
	
	static void Update(float deltaTime);
	
	static void EnableCanvasByID(std::string id);

	static void Clean();
	
	static Canvas* GetCanvasByID(std::string id);
};

