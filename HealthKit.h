#pragma once

#include "Prop.h"

class HealthKit : public Prop
{
private:
	
	float healAmount;
	
public:
	HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger);
	~HealthKit();
	
	void PickUp();
};

