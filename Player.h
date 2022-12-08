#pragma once
#include "GameObject.h"
#include "InputManager.h"



class Player : public GameObject
{
private:
	
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	RigidBody* rigidBody;
	Collider* collider;
	
	float moveSpeed = 100;
	
public:

	Player();
	~Player();
	
	void Update(float deltaTime);
	void Draw();
};

