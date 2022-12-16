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
	bool isStatic;
	Collider* currentCollidedObject = nullptr;
	SDL_Rect* colliderRect;
	std::function <void(Collider* other)> OnCollisionEnterEvent;
	
public:
	
	Transform* owner;

	virtual void SetUp(Transform* owner, Vector2 size, bool isStatic = false);

	virtual void Update() {};

	virtual void Draw() {};

	void OnCollision(Collider* other);

	inline Vector2 GetPosition() { return Vector2(colliderRect->x, colliderRect->y); }

	Vector2 GetCentre();

	virtual SDL_Rect* GetColliderRect() { return colliderRect; };
};