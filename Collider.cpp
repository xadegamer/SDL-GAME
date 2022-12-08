#include "Collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{
}

void Collider::someFunc()
{
}

void Collider::SetUp(Transform* owner, Vector2 size, Vector2 offset)
{
	this->owner = owner;
	collisionBox.w = size.x;
	collisionBox.h = size.y;
	this->offset = offset;
}	

void Collider::Update()
{	
	collisionBox.x = owner->position.x + offset.x;
	collisionBox.y = owner->position.y + offset.y;
}

void Collider::Draw()
{
	// Draw the collision box for debugging green
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &collisionBox);
}
