#pragma once

#include "SDLManager.h"
#include "UIObject.h"

class Canvas
{
	static std::vector<Canvas*> activeCanvases;
	static void EnableCanvasByID(std::string id);
	
public:
	Canvas(std::string id, Vector2 size, Vector2 position, bool hasBackground = true);
	~Canvas();
	
	SDL_Rect background;

	std::string ID;
	
	bool isActive;
	bool isEnable;
	bool hasBackground;
	
	std::vector<UIObject*> uiObjects;
	
	void Show();
	
	void Hide();
	
	void AddUIObject(UIObject* uiObject);
	
	void Draw();

	void Update();
};

