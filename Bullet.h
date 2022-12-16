#pragma once

#include "GameObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

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
	CircleCollider* circleCollider;
	float moveSpeed = 500;
	BulletType bulletType;

public:

	
	Bullet(Vector2 startPosition, BulletType bulletType, Vector2 direction = Vector2(0, 0));
	~Bullet();

	void Update(float deltaTime) override;
	void Draw() override;	
	
	void OnCollisionEnter(Collider* other) override;

	bool IsOutSideScreen();

	void RemoveBullet();
	
	inline BulletType GetBulletType() { return bulletType; }
};

