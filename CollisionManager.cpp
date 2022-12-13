#include "CollisionManager.h"

const static int s_buffer = 4;

bool CollisionManager::DoBoxToBoxCollisionCheck(SDL_Rect* A, SDL_Rect* B, int buffer = 2)
{
	if (A->x + A->w - buffer > B->x && A->x + buffer < B->x + B->w && A->y + A->h - buffer > B->y && A->y + buffer < B->y + B->h)
	{
		return true;
	}
	return false;
}

bool CollisionManager::DoCircleToCircleCollsionCheck(SDL_Rect* a, SDL_Rect* b)
{
	// calculate total radius squared
	float aRadius = a->w / 2;
	float bRadius = b->w / 2;
	float totalRadiusSquared = aRadius + bRadius;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
	// if the distance between the centers of the circles is less than the sum of their radii
	if (DistanceSquared(a->x, a->y, b->x, b->y) <= totalRadiusSquared)
	{
		// then the circles have collided
		return true;
	}
	// otherwise the circles have not collided
	return false;
}

bool CollisionManager::DoBoxToCircleCollsionCheck(SDL_Rect* box, SDL_Rect* circle)
{
	//Closest point on collision box
	int cX, cY;
	float circleRadius = circle->w / 2;

	//Find closest x offset
	if (circle->x < box->x)
	{
		cX = box->x;
	}
	else if (circle->x > box->x + box->w)
	{
		cX = box->x + box->w;
	}
	else
	{
		cX = circle->x;
	}

	//Find closest y offset
	if (circle->y < box->y)
	{
		cY = box->y;
	}
	else if (circle->y > box->y + box->h)
	{
		cY = box->y + box->h;
	}
	else
	{
		cY = circle->y;
	}

	//If the closest point is inside the circle
	if (DistanceSquared(circle->x, circle->y, cX, cY) < circleRadius * circleRadius)
	{
		//This box and the circle have collided
		return true;
	}

	//If the shapes have not collided
	return false;
}

bool CollisionManager::CheckCollision(Collider* colA, Collider* colB)
{
	BoxCollider* boxA = dynamic_cast<BoxCollider*>(colA);
	BoxCollider* boxB = dynamic_cast<BoxCollider*>(colB);

	CircleCollider* circleA = dynamic_cast<CircleCollider*>(colA);
	CircleCollider* circleB = dynamic_cast<CircleCollider*>(colB);

	if (boxA != nullptr && boxB != nullptr)
	{
		return DoBoxToBoxCollisionCheck(boxA->GetColliderRect(), boxB->GetColliderRect(), s_buffer);
	}
	else if (circleA != nullptr && circleB != nullptr)
	{
		return DoCircleToCircleCollsionCheck(circleA->GetColliderRect(), circleB->GetColliderRect());
	}
	else if (boxA != nullptr && circleB != nullptr)
	{
		return DoBoxToCircleCollsionCheck(boxA->GetColliderRect(), circleB->GetColliderRect());
	}
	else if (circleA != nullptr && boxB != nullptr)
	{
		return DoBoxToCircleCollsionCheck(boxB->GetColliderRect(), circleA->GetColliderRect());
	}
}

double CollisionManager::DistanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

