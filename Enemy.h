#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
private:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	Collider* collider;

public:

	Enemy(Vector2 startPosition);
	~Enemy();

	void Update(float deltaTime) override;
	void Draw() override;
};

