#include "HealthKit.h"

#include "Player.h"

HealthKit::HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount) : Collectable(position, spriteName, colliderType, sortingOrder, amount)
{
	tag = Tag::DEFAULT;
	collider->OnCollisionEnterEvent = std::bind(&HealthKit::OnCollisionEnter, this, std::placeholders::_1);
}

HealthKit::~HealthKit()
{
	
}

void HealthKit::PickUp(Player* player)
{
	if (player->GetComponent<HealthComponent>()->Heal(amount))
	{
		Collectable::PickUp(player);
	}
}