#pragma once

#include <iostream>

#include "GameObject.h"

class VfxEffect : public GameObject
{
	
private:

	float clearTime = 2.0f;
	float currentLifeTime = 0;
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	bool isDestroyed = false;
	
public:

	VfxEffect(std::string ID, int numberOfFrame);
	~VfxEffect();

	void Update(float deltaTime) override;

	void Draw() override;

	void OnAnimationEnd();
};

