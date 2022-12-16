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
	bool exploded;
	
public:
	GasCylinder(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger);
	~GasCylinder();

	void Update(float deltaTime) override;
	void TriggerExplosion();
	void Explosion();
};

