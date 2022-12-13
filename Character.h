#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include <iostream>

class Character : public GameObject
{
protected:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	float moveSpeed = 100;
	
public:

	Character();
	~Character();

	virtual void Update(float deltaTime) override;
	void Draw() override;
};

