#pragma once

#include "Prop.h"

class HealthKit : public Prop
{
private:
	
	float healAmount;
	
public:
	HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder);
	~HealthKit();
	
	void OnCollisionEnter(Collider* other) override;
	void PickUp();
};

