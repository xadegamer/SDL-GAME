#pragma once

#include "SDLManager.h"

class Game;
class Player;
struct Vector2;


class Camera
{
	Camera() = delete;
	~Camera() = delete;
	
	static SDL_Rect camera;
	static Player* player;

public:

	static void SetUp(Player* player);
	static void Update();
	static Vector2 GetPosition();
	static void Clean();
};

