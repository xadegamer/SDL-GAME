#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include "Health.h"

#include <iostream>

class Character : public GameObject
{
protected:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
	Health* health;
	
	float maxHealth;
	float moveSpeed = 100;
	
public:

	Character();
	~Character();

	void Draw() override;

	virtual void OnShootEvent() {};

	virtual void OnHealthChange(float health) {};

	virtual void OnDeath() {};

	inline Health* GetHealth() { return health; }
};

