#include "CircleCollider.h"

void CircleCollider::SetUp(Transform* owner, Vector2 size, Vector2 offset, bool relativeToCam)
{
	Collider::SetUp(owner, size, offset, relativeToCam);

	radious = colliderRect->w / 2;
}

void CircleCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);

	for (int i = 0; i < 360; i++)
	{
		float x = radious * cos(i * 3.14 / 180);
		float y = radious * sin(i * 3.14 / 180);

		SDL_RenderDrawPoint(SDLManager::GetRenderer(), colliderRect->x + x, colliderRect->y + y);
	}
}
