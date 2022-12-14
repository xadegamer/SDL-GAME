#pragma once

#include "SDLManager.h"
#include "UIObject.h"
#include <vector>

class Canvas : public UIObject
{
private:

	Sprite* backgroundSprite;
	bool isActive;
	bool isEnable;
	bool hasBackground;

public:
	Canvas(std::string id, Vector2 size, Vector2 position, bool hasBackground = true);
	~Canvas();
	
	std::vector<UIObject*> uiObjects;
	
	void Show();
	
	void Hide();
	
	void AddUIObject(UIObject* uiObject);
	
	void Draw();

	void Update();

	UIObject* GetUIObjectByID(std::string id);

};

