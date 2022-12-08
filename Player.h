#pragma once
#include "GameObject.h"
#include "InputManager.h"


class Player : public GameObject
{
private:
	
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	RigidBody* rigidBody;
	
	float moveSpeed = 3.0f;
	
public:

	Player();
	~Player();
	
	void Update();
	void Draw();
};

