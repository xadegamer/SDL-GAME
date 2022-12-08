#include "CollisionManager.h"

const static int s_buffer = 4;

bool CollisionManager::CheckCollision(SDL_Rect* A, SDL_Rect* B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A->x;
	rightA = A->x + A->w;
	topA = A->y;
	bottomA = A->y + A->h;

	//Calculate the sides of rect B
	leftB = B->x;
	rightB = B->x + B->w;
	topB = B->y;
	bottomB = B->y + B->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) return false;

	if (topA >= bottomB) return false;

	if (rightA <= leftB) return false;

	if (leftA >= rightB) return false;

	//If none of the sides from A are outside B
	return true;
}

bool CollisionManager::CheckCollision(SDL_Rect* A, SDL_Rect* B, int buffer)
{
	int aHBuf = A->h / s_buffer;
	int aWBuf = A->w / s_buffer;
	int bHBuf = B->h / s_buffer;
	int bWBuf = B->w / s_buffer;
	// if the bottom of A is less than the top of B - no collision
	if ((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }
	// if the top of A is more than the bottom of B = no collision
	if (A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }
	// if the right of A is less than the left of B - no collision
	if ((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }
	// if the left of A is more than the right of B - no collision
	if (A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }
	// otherwise there has been a collision
	return true;
}
