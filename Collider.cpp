#include "Collider.h"

Collider::Collider()
{
	colliderRect = new SDL_Rect();
}

Collider::~Collider()
{
	colliderRect = nullptr;
}

void Collider::someFunc()
{
}

void Collider::SetUp(ColliderType colType,Transform* owner, Vector2 size, Vector2 offset)
{
	this->type = colType;
	this->owner = owner;
	this->offset = offset;
	
	colliderRect->w = size.x;
	colliderRect->h = size.y;
}	

void Collider::Update()
{	
	colliderRect->x = owner->position.x + offset.x;
	colliderRect->y = owner->position.y + offset.y;
}

void Collider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 255, 0, 255);
	
	if (type == Box)
	{
		SDL_RenderDrawRect(SDLManager::GetRenderer(), colliderRect);
	}
	else
	{
		float radious = colliderRect->w / 2;
		for (int i = 0; i < 8; i++)
		{
			float x = radious * cos(i * 3.14 / 4);
			float y = radious * sin(i * 3.14 / 4);
			SDL_RenderDrawLine(SDLManager::GetRenderer(), colliderRect->x + colliderRect->w / 2, colliderRect->y + colliderRect->h / 2, colliderRect->x + colliderRect->w / 2 + x, colliderRect->y + colliderRect->h / 2 + y);
		}
	}
}
