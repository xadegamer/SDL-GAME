#pragma once
#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "TimeManager.h"

#include "UIManager.h"

#include <iostream>

extern TimeManager systemTimer;

class Game;

class Player : public Character
{
private:
	
	CircleCollider* circleCollider;
	float moveSpeed = 100;
	
public:

	Player(Vector2 startPosition, float maxhealth);
	~Player();
	
	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;
	
	void OnCollisionEnter(Collider* other) override;

	void OnShootEvent();
	
	void OnHealthChange(float health) override;

	void OnTakeDamage() override;
	
	void OnHeal() override;

	void OnDeath() override;
	
	void OnDead() override;
};

