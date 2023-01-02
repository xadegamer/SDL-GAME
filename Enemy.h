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
	static int numberOfEnemiesAlive;
	
	static std::function<void(int)> OnAnyEnemyDespawned;
	static std::function<void(int)> OnAnyEnemyKilled;
	
	float fireRate;
	float fireTimer;
	
	float despawnRate;
	float despawnTimer;
	
	float minAttackRange;
	float MaxAttackRange;
	float detectionRadius;

	EnemyState currentEnemyState;

	Vector2 spawnPoint;
	Vector2 currentPatrolPoint;
	Vector2 direction;

	GameObject* target;
	
public:
	
	static inline std::function <void(int)>& GetOnAnyEnemyKilled() { return OnAnyEnemyKilled; }
	static inline std::function <void(int)>& GetOnAnyEnemyDespawned() { return OnAnyEnemyDespawned; }
	static inline int GetNumberOfEnemyAlive() { return noOfEnemies; }

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

	GameObject* GetTarget();
};

