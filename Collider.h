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

#include <stdio.h>

enum  ColliderType
{
	Box, Circle
};

class Collider : public Component
{
private:
	bool isRelativeToCam;
	
public:

	Collider();
	~Collider();
	void someFunc();
	Vector2 offset;
	void (*OnCollisionEnter)(Collider* other);

	Collider* currentCollidedObject = nullptr;
	
public:
	
	ColliderType type;
	Transform* owner;
	SDL_Rect* colliderRect;

	void SetUp(ColliderType colType, Transform* owner, Vector2 size, Vector2 offset = Vector2(0, 0), bool relativeToCam = true);

	void Update();

	void AssignCollisonCallBack(void (*OnCollisionEnter)(Collider* other));

	void OnCollision(Collider* other);
		
	virtual void Draw();

	inline Vector2 GetPosition() { return Vector2(colliderRect->x, colliderRect->y); }

	Vector2 GetForward();

	Vector2 GetRight();
};