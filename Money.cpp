#include "Money.h"

Money::Money(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount) : Collectable(position, spriteName, colliderType, sortingOrder, amount)
{
	
}

Money::~Money()
{
}

void Money::Update(float deltaTime)
{
	Collectable::Update(deltaTime);
}

void Money::PickUp(Player* player)
{
	//player->GetComponent<MoneyComponent>()->AddMoney(amount);
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("Pick Up"), false);
	Collectable::PickUp(player);
}
