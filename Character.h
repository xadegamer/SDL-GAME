#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include "HealthComponent.h"

#include "Bullet.h"

#include <iostream>

class Character : public GameObject
{
protected:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	HealthComponent* health;
	
	float maxHealth;
	float moveSpeed = 100;
	float runSpeed = 200;
	float currentMoveSpeed;
	
	bool canMove = true;
	bool isDead = false;
	
public:

	Character(Vector2 position);
	~Character();

	virtual void Update(float deltaTime) override;

	void Draw() override;

	virtual void OnShootEvent() {};

	virtual void OnHealthChange(float health) {};
	
	virtual void OnTakeDamage() {};
	
	virtual void OnHeal() {};

	virtual void OnDeath() {};

	virtual void OnDead();

	Vector2 GetBulletSpawnLocation(Vector2 playerPos);

	void SpawnBullet(Vector2 spawnPos, Vector2 direction, BulletType type);

	inline HealthComponent* GetHealth() { return health; }
};

