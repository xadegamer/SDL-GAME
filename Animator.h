#pragma once
#include "Component.h"
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2.h"

#include "SpriteRenderer.h"

struct AnimationClip
{
	SpriteRenderer* spriteRenderer;
	int animPixelHeight; //pixel height of a single animation frame.
	int animPixelWidth;//pixel width of a single animation frame.
	int animState;//which row on the spritesheet we want to go through.
	int animFrame = 1;//how many sprites are on the current row/state.
	float timeInAnimtionState;//this is used to calculate which frame of the animation should be shown depending on time
	float animSpeed;//a multiplier for how fast to play the animation.

	AnimationClip(SpriteRenderer* spriteRenderer)
	{
		this->spriteRenderer = spriteRenderer;
	}
};

class Animator : public Component
{
public:

	  Animator();
	  ~Animator();
};
