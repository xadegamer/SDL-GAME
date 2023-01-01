#pragma once

#include "Prop.h"
#include "AnimationControlledVfxEffect.h"

class GasCylinder : public Prop
{
private:
	
	float detonateTime;
	float currentLifeTime;
	float explosionRadius;
	float damage;
	bool hasTriggerExplosion;
	bool exploded;

	AnimationControlledVfxEffect* smokeEffect;
	
public:
	GasCylinder(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger);
	~GasCylinder();

	void Update(float deltaTime) override;
	void TriggerExplosion();
	void Explosion();
};

