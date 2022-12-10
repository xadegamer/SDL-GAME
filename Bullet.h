#pragma once

#include "GameObject.h"

enum class BulletType
{
	PLAYER,
	ENEMY
};

class Bullet : public GameObject
{
	
private:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	Collider* collider;
	float moveSpeed = 500;

public:

	BulletType bulletType;
	
	Bullet(Vector2 startPosition, BulletType bulletType, Vector2 direction = Vector2(0, 0));
	~Bullet();

	void Update(float deltaTime) override;
	void Draw() override;
	
	bool IsOutSideScreen();
};

