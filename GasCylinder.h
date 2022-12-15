#pragma once

#include "Prop.h"

class GasCylinder : public Prop
{
private:
	
	float detonateTime = 0.5f;
	float currentLifeTime = 0;
	float explosionRadius = 200;
	float damage = 100;
	bool hasTriggerExplosion;
	
public:
	GasCylinder(std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger);
	~GasCylinder();

	void Update(float deltaTime) override;
	void TriggerExplosion();
	void Explosion();
};

