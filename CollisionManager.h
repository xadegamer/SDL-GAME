#pragma once

#include "SDLManager.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool CheckCollision(SDL_Rect* A, SDL_Rect* B);
	

	bool CheckCollision(SDL_Rect* A, SDL_Rect* B, int buffer);
};

