#include "Collectable.h"

#include "Player.h"

Collectable::Collectable(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount) : Prop(position, spriteName, colliderType, sortingOrder, true, false)
{
	this->amount = amount;
}

Collectable::~Collectable()
{
}

void Collectable::OnCollisionEnter(Collider* other)
{
	Player* player = dynamic_cast<Player*>(other->GetGameObject());
	if (player)	PickUp(player);
}

void Collectable::PickUp(Player* player)
{
	isDestroyed = true;
	Destroy(this);
}