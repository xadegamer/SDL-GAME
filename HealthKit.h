#pragma once

#include "Collectable.h"

class HealthKit : public Collectable
{	
public:
	HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount);
	~HealthKit();

	virtual void Update(float deltaTime) override;
	
	void PickUp(Player* player) override;
};

