#pragma once
#include <iostream>

#include "InputManager.h"

using namespace std;

#define PI 3.14159265358979323846


static float GetAngleFromTraget(Vector2 position, Vector2 target, float width, float height)
{
	float x = target.x - (position.x + width / 2);
	float y = target.y - (position.y + height / 2);
	return 90 + atan2(y, x) * 180 / PI;
}

static Vector2 GetDirectionToTarget(Vector2 position, Vector2 target)
{
	float x = target.x - position.x;
	float y = target.y - position.y;
	return Vector2(x, y).normalize();
}

static float GetAngleFromMouse(Vector2 position, float width, float height)
{
	return GetAngleFromTraget(position, InputManager::GetMousePosition(), width, height);
}

static Vector2 GetDirectionToMouse(Vector2 position)
{
	return GetDirectionToTarget(position, InputManager::GetMousePosition());
}