#pragma once

#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


enum  EnemyState
{
	PATROL,
	CHASE,
	DEAD
};

class Enemy : public Character
{
private:
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

	Enemy(Vector2 position, float maxhealth);
	~Enemy();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;

	void OnShootEvent() override;

	void OnTakeDamage() override;
	
	void OnDeath() override;
	
	void PatrolState(float deltaTime);

	void ChaseState(float deltaTime);

	void AttackState();

	void EnemyDespawn();

	bool PlayerInRange(float range);
};

