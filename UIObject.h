#pragma once

#include "SDLManager.h"
#include "AssetManager.h"
#include "MathUtility.h"
#include "Vector2.h"
#include "Transform.h"
#include "InputManager.h"


#include <iostream>
#include <functional>

class UIObject
{
protected:
	
	static std::vector<UIObject*> activeUIObjects;
	
public:
	
	Vector2 anchorPositon;
	Vector2 size;
	
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Color color;

	int layer = 0;
	bool isStatic;
	
	UIObject();
	virtual ~UIObject();

	virtual void Draw();
	virtual void Update();

	static void Destroy(UIObject*  uiObject);
	static void DestroyAll();
};

