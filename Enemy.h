#pragma once

#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <functional>



enum  EnemyState
{
	PATROL,
	CHASE,
	DEAD
};

class Enemy : public Character
{
private:

	static int noOfEnemies;

	
	BoxCollider* boxCollider;
	CircleCollider* circleCollider;
	
	float fireRate;
	float fireTimer;
	
	float despawnRate;
	float despawnTimer;
	
	float attackRange;
	float detectionRadius;

	EnemyState currentEnemyState;

	Vector2 spawnPoint;
	Vector2 currentPatrolPoint;
	Vector2 direction;
	
public:
	
	static std::function<void(int)> OnAnyEnemyKilled;

	Enemy(Vector2 position, float maxhealth);
	~Enemy();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;

	void OnShootEvent() override;

	void OnTakeDamage() override;
	
	void OnDeath() override;
	
	void PatrolState(float deltaTime);

	void ChaseState(float deltaTime);

	void EnemyDespawn();

	bool PlayerInRange(float range);
};

