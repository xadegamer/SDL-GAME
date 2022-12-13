#pragma once

#include "Component.h"
#include "Vector2.h"

class Transform : public Component
{
private:
	Vector2 lastSafePosition;
	
public:
	Transform();
	~Transform();
	
	void Translate(Vector2 translation);

	void TranslateX(float x);

	void TranslateY(float y);

	void Log();

	Vector2 position;
	Vector2 scale;
	float rotation;

	Vector2 GetForward();

	Vector2 GetRight();
};

