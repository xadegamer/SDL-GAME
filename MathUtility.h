#pragma once
#include <iostream>

using namespace std;

#define PI 3.14159265358979323846


const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

float GetAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}