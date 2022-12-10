#pragma once
#include "GameObject.h"

#include <iostream>

class Game;

class Player : public GameObject
{
private:
	
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	RigidBody* rigidBody;
	Collider* collider;
	
	float moveSpeed = 100;

	//list of bullets

	
public:

	Player();
	~Player();
	
	void Update(float deltaTime) override;
	void Draw() override;
};

