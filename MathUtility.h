#pragma once
#include <iostream>

using namespace std;

#define PI 3.14159265358979323846

float GetAngleFromMouse(Vector2 position, float width, float height)
{
	Vector2 vec = InputManager::GetMousePosition();
	float x = vec.x - (position.x + width / 2);
	float y = vec.y - (position.y + height / 2);
	return 90 + atan2(y, x) * 180 / PI;
}