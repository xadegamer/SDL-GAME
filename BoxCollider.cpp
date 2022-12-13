#include "BoxCollider.h"


void BoxCollider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(SDLManager::GetRenderer(), colliderRect);
}
