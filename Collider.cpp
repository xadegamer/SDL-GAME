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

void Collider::SetUp(Transform* owner, Vector2 size, Vector2 offset, bool isStatic)
{
	this->owner = owner;
	this->offset = offset;
	this->isStatic = isStatic;
	
	colliderRect->w = size.x;
	colliderRect->h = size.y;
}	

void Collider::Update()
{	
	if (isStatic)
	{
		colliderRect->x = owner->position.x + offset.x;
		colliderRect->y = owner->position.y + offset.y;
	}
	else
	{
		colliderRect->x = (owner->position.x + offset.x) - Camera::GetPosition().x;
		colliderRect->y = (owner->position.y + offset.y) - Camera::GetPosition().y;
	}
}

void Collider::OnCollision(Collider* other)
{
	if (OnCollisionEnterEvent != nullptr)OnCollisionEnterEvent(other);
	
	if (other->isTrigger && OnTriggerEnterEvent != nullptr) OnTriggerEnterEvent(other);
	
	//if(OnCollisionEnter != nullptr && currentCollidedObject != other)
	//{
	//	currentCollidedObject = other;
	//	OnCollisionEnter(other);
	//}
}

Vector2 Collider::GetForward()
{
	return Vector2::Normalize(Vector2(colliderRect->x, colliderRect->y));
}

Vector2 Collider::GetRight()
{
	return Vector2::Normalize(Vector2(colliderRect->x, -colliderRect->x));
}
