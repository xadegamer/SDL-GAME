#pragma once

#include <iostream>

#include "GameObject.h"

class VfxEffect : public GameObject
{
	
private:
	
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	
public:

	VfxEffect(Vector2 position, std::string ID, int numberOfFrame, bool applyOffset = true);
	~VfxEffect();

	void Update(float deltaTime) override;

	void Draw() override;

	void OnAnimationEnd();
};

