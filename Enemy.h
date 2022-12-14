#pragma once

#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

class Enemy : public Character
{
private:
	BoxCollider* boxCollider;
	CircleCollider* circleCollider;
	
	float fireRate = 3;
	float fireTimer;
	
public:

	Enemy(Vector2 startPosition, float maxhealth);
	~Enemy();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;

	void OnTriggerEnter(Collider* other) override;

	void OnShootEvent() override;

	void OnTakeDamage() override;
	
	void OnDeath() override;
	
	void Patrol();
};

