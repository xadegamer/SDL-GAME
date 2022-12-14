#pragma once

#include "SDLManager.h"
#include "UIObject.h"

class Canvas : public UIObject
{
public:
	Canvas(std::string id, Vector2 size, Vector2 position, bool hasBackground = true);
	~Canvas();
	
	Sprite* backgroundSprite;
	
	bool isActive;
	bool isEnable;
	bool hasBackground;
	
	std::vector<UIObject*> uiObjects;
	
	void Show();
	
	void Hide();
	
	void AddUIObject(UIObject* uiObject);
	
	void Draw();

	void Update();

	UIObject* GetUIObjectByID(std::string id);
};

