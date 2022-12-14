#include "CircleCollider.h"

void CircleCollider::SetUp(Transform* owner, Vector2 size, float radiousMutiplier, Vector2 offset , bool isStatic)
{
	Collider::SetUp(owner, size, offset, isStatic);
	radius = colliderRect->w / (2 * radiousMutiplier);
}

void CircleCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);

	Vector2 centre = GetCentre();
	
	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * 3.14 / 180);
		float y = radius * sin(i * 3.14 / 180);

		SDL_RenderDrawPoint(SDLManager::GetRenderer(), centre.x + x, centre.y + y);
	}
}
