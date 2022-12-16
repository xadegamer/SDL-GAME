#pragma once

#include "Collectable.h"

class HealthKit : public Collectable
{	
public:
	HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount);
	~HealthKit();
	
	void PickUp(Player* player) override;
};

