#pragma once

#include "SDLManager.h"
#include "GameObject.h"
#include "AssetManager.h"
//A circle stucture
//struct Circle
//{
//	int x, y;
//	int r;
//};

class Collider : public Component
{
public:

	Collider();
	~Collider();
	void someFunc();
	
public:
	Transform* owner;
	SDL_Rect collisionBox;
	Vector2 offset;

	void SetUp(Transform* owner, Vector2 size, Vector2 offset = Vector2(0, 0));
	void Update();
	void Draw();
};