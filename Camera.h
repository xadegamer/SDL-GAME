#pragma once

#include "SDLManager.h"

class GameObject;
struct Vector2;


class Camera
{
	Camera() = delete;
	~Camera() = delete;
	
	static SDL_Rect viewBox;
	static GameObject* player;

public:

	static void SetUp(GameObject* player);
	static void Update();
	static Vector2 GetPosition();
	static SDL_Rect GetViewBox() { return viewBox; }
};

