#pragma once

#include <iostream>
#include <functional>
#include <vector>

class Canvas;
class Game;

class UIManager
{
private:
	UIManager() = delete;
	~UIManager() = delete;
	
public:

	static std::vector<Canvas*> activeCanvases;
	
	static void Init();
	
	static void SetUpMainMenuCanvas();
	
	static void SetUpOptionCanvas();

	static void SetUpGameCanvas();

	static void SetUpPauseCanvas();
	
	static void Draw();
	
	static void Update();
	
	static void EnableCanvasByID(std::string id);
};

