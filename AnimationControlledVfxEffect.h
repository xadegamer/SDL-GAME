#pragma once

#include <iostream>

#include "GameObject.h"

class AnimationControlledVfxEffect : public GameObject
{
	
private:
	
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	
public:

	AnimationControlledVfxEffect(Vector2 position, std::string ID, int numberOfFrame, int sortingOrder, bool applyOffset = true, bool destroyOnLastFrame = true);
	~AnimationControlledVfxEffect();

	void Update(float deltaTime) override;

	void Draw() override;

	void OnAnimationEnd();
};

