#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "AudioManager.h"
#include "AssetManager.h"

class Canvas;
class Game;

class UIManager
{
private:
	UIManager() = delete;
	~UIManager() = delete;
	
	static float refreshRate;
	static float currrentRefreshRate;
	
public:

	static std::vector<Canvas*> activeCanvases;
	
	static void Init();
	
	static void SetUpMainMenuCanvas();
	
	static void SetUpOptionCanvas();

	static void SetUpGameCanvas();

	static void SetUpPauseCanvas();
	
	static void Draw();
	
	static void Update(float deltaTime);
	
	static void EnableCanvasByID(std::string id);

	static void Clean();
};

