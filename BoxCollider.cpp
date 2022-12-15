#include "BoxCollider.h"

#include "Camera.h"

void BoxCollider::SetUp(Transform* owner, Vector2 size, float sizeMutiplier, bool isStatic)
{
	Collider::SetUp(owner, size, isStatic);
	boxColliderRect = new SDL_Rect();
	boxColliderRect->w = size.x * sizeMutiplier;
	boxColliderRect->h = size.y * sizeMutiplier;
	boxColliderRect->x = GetCentre().x - boxColliderRect->w / 2;
	boxColliderRect->y = GetCentre().y - boxColliderRect->h / 2;
}

void BoxCollider::Update()
{
	if (!isEnabled || isStatic) return;
	colliderRect->x = owner->GetPosition().x;
	colliderRect->y = owner->GetPosition().y;
	boxColliderRect->x = GetCentre().x - boxColliderRect->w / 2;
	boxColliderRect->y = GetCentre().y - boxColliderRect->h / 2;
}

void BoxCollider::Draw()
{
	if (!isEnabled) return;
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_Rect rect = *boxColliderRect;
	rect.x -= Camera::GetPosition().x;
	rect.y -= Camera::GetPosition().y;
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &rect);
}
