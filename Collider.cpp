#include "Collider.h"

#include "Camera.h"

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

void Collider::SetUp(ColliderType colType,Transform* owner, Vector2 size, Vector2 offset, bool relativeToCam)
{
	this->type = colType;
	this->owner = owner;
	this->offset = offset;
	isRelativeToCam = relativeToCam;
	
	colliderRect->w = size.x;
	colliderRect->h = size.y;
}	

void Collider::Update()
{	
	if (isRelativeToCam)
	{
		colliderRect->x = (owner->position.x + offset.x) - Camera::GetPosition().x;
		colliderRect->y = (owner->position.y + offset.y) - Camera::GetPosition().y;
	}
	else
	{
		colliderRect->x = owner->position.x + offset.x;
		colliderRect->y = owner->position.y + offset.y;
	}
}

void Collider::AssignCollisonCallBack(void(*OnCollisionEnter)(Collider* other))
{
	this->OnCollisionEnter = OnCollisionEnter;
}

void Collider::OnCollision(Collider* other)
{
	if (OnCollisionEnter != nullptr)OnCollisionEnter(other);
	
	//if(OnCollisionEnter != nullptr && currentCollidedObject != other)
	//{
	//	currentCollidedObject = other;
	//	OnCollisionEnter(other);
	//}
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
		for (int i = 0; i < 360; i++)
		{
			float x = radious * cos(i * 3.14 / 180);
			float y = radious * sin(i * 3.14 / 180);

			SDL_RenderDrawPoint(SDLManager::GetRenderer(), colliderRect->x + x, colliderRect->y + y);
		}
	}
}

Vector2 Collider::GetForward()
{
	return Vector2::Normalize(Vector2(colliderRect->x, colliderRect->y));
}

Vector2 Collider::GetRight()
{
	return Vector2::Normalize(Vector2(colliderRect->x, -colliderRect->x));
}
