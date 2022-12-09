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

enum  ColliderType
{
	Box, Circle
};

class Collider : public Component
{
public:

	Collider();
	~Collider();
	void someFunc();

	Vector2 offset;
	
public:
	
	ColliderType type;
	Transform* owner;
	SDL_Rect* colliderRect;

	void SetUp(ColliderType colType, Transform* owner, Vector2 size, Vector2 offset = Vector2(0, 0));
	void Update();
	virtual void Draw();

	inline Vector2 GetPosition() { return Vector2(colliderRect->x, colliderRect->y); }
};