#pragma once
#include <iostream>

using namespace std;

#define PI 3.14159265358979323846

float GetAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

float GetAngleFromVector(Vector2 v1, Vector2 v2)
{
	//float angle = -90 + atan2(v1.y - v2.y, v1.x - v2.x) * (180 / PI);
	//return angle >= 0 ? angle : 360 + angle;

    int DeltaX;
    int DeltaY;
    double result;
    DeltaX = v1.x - v2.x;
    DeltaY = v1.y - v2.y;
    result = (atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;

	float angle = atan2(v1.y - v2.y, v1.x - v2.x) * (180 / PI);
    return result;
}