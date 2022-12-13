#pragma once
#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "TimeManager.h"

#include <iostream>

extern TimeManager systemTimer;

class Game;

class Player : public Character
{
private:
	
	CircleCollider* circleCollider;
	float moveSpeed = 100;
	
public:

	Player(Vector2 startPosition);
	~Player();
	
	void Update(float deltaTime) override;
	
	void OnCollisionEnter(Collider* other) override;

	void OnTriggerEnter(Collider* other) override;

	void OnShootEvent();
};

