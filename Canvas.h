#pragma once

#include "SDLManager.h"
#include "UIObject.h"

class Canvas
{
	static std::vector<Canvas*> activeCanvases;
	static void EnableCanvasByID(std::string id);
	
public:
	Canvas(std::string id, Vector2 size, Vector2 position);
	~Canvas();
	
	SDL_Rect background;

	std::string ID;
	bool isActive;
	std::vector<UIObject*> uiObjects;
	
	void Show();
	
	void Hide();
	
	void AddUIObject(UIObject* uiObject);
	
	void Draw();

	void Update();
};

