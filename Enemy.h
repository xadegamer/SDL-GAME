#pragma once

#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

class Enemy : public Character
{
private:
	BoxCollider* boxCollider;
	CircleCollider* circleCollider;
	
public:

	Enemy(Vector2 startPosition);
	~Enemy();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;

	void OnTriggerEnter(Collider* other) override;
};

