#pragma once

#include "SDLManager.h"
#include "GameObject.h"
#include "AssetManager.h"
#include <stdio.h>
#include <functional>

class Collider : public Component
{
private:

	
public:

	Collider();
	~Collider();
	void someFunc();
	Vector2 offset;
	bool isTrigger;
	Collider* currentCollidedObject = nullptr;

	std::function <void(Collider* other)> OnCollisionEnterEvent;
	std::function <void(Collider* other)> OnTriggerEnterEvent;
	
public:
	
	Transform* owner;
	SDL_Rect* colliderRect;
	bool isStatic;
	
	virtual void SetUp(Transform* owner, Vector2 size, Vector2 offset = Vector2(0, 0), bool relativeToCam = false);

	void Update();

	virtual void Draw() {};

	void OnCollision(Collider* other);

	inline Vector2 GetPosition() { return Vector2(colliderRect->x, colliderRect->y); }

	Vector2 GetForward();

	Vector2 GetRight();

	Vector2 GetCentre();

	inline SDL_Rect* GetColliderRect() { return colliderRect; }
};