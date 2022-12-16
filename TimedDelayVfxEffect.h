#pragma once

#include <iostream>

#include "GameObject.h"

class TimedDelayVfxEffect : public GameObject
{
	
private:

	float duration;
	float currentLifeTime = 0;
	
	SpriteRenderer* spriteRenderer;
	bool isDestroyed = false;

public:

	TimedDelayVfxEffect(Vector2 position, std::string spriteID, int sortingOrder, float duration);
	~TimedDelayVfxEffect();

	void Update(float deltaTime) override;

	void Draw() override;
};

