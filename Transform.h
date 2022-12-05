#pragma once

#include "Component.h"
#include "Vector2.h"

class Transform : public Component
{
	
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
};

