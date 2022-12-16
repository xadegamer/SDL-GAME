#pragma once

#include "Collectable.h"

class Money : public Collectable
{
public:
	Money(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount);

	~Money();

	void Update(float deltaTime) override;

	void PickUp(Player* player) override;
};

