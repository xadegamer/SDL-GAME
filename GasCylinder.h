#pragma once

#include "Prop.h"

class GasCylinder : public Prop
{
private:
	
	float currentLifeTime = 0;
	float clearTime = 2.0f;
	float explosionRadius = 100;
	float damage = 100;
	
public:
	GasCylinder(std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger);
	~GasCylinder();

	void Explosion();
};

