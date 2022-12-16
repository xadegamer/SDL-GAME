#include "HealthKit.h"

#include "Player.h"

HealthKit::HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount) : Collectable(position, spriteName, colliderType, sortingOrder, amount)
{

}

HealthKit::~HealthKit()
{
	
}

void HealthKit::Update(float deltaTime)
{
	Collectable::Update(deltaTime);
}

void HealthKit::PickUp(Player* player)
{
	if (player->GetComponent<HealthComponent>()->Heal(amount))
	{
		Collectable::PickUp(player);
	}
}