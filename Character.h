#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include "Health.h"

#include "Bullet.h"

#include <iostream>

class Character : public GameObject
{
protected:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	Health* health;
	
	float maxHealth;
	float moveSpeed = 100;
	
	bool canMove = true;
	bool isDead = false;
	
public:

	Character();
	~Character();

	void Draw() override;

	virtual void OnShootEvent() {};

	virtual void OnHealthChange(float health) {};
	
	virtual void OnTakeDamage() {};
	
	virtual void OnHeal() {};

	virtual void OnDeath() {};

	virtual void OnDead();

	Vector2 GetBulletSpawnLocation(Vector2 playerPos);

	void SpawnBullet(Vector2 spawnPos, Vector2 direction, BulletType type);

	inline Health* GetHealth() { return health; }
};

