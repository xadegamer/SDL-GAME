
#include "Animator.h"

Animator::Animator()
{
	
}

Animator::~Animator()
{
	currentAnimationClip = nullptr;
	lastAnimationClip = nullptr;
}


void Animator::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

AnimationClip* Animator::AddAnimationClip(std::string name, Sprite* sprite, int numberOfCells, float animSpeed, bool loop)
{
	AnimationClip* animClip = new AnimationClip(name, sprite, numberOfCells, animSpeed, loop);
	animationClips.push_back(animClip);
	if (currentAnimationClip == nullptr) SwitchAnimation(animClip);
	return animClip;
}

void Animator::ChangeAnimation(std::string name, bool thisWaitTillFinish)
{
	if(waitTillFinish || (currentAnimationClip != nullptr && currentAnimationClip->name == name)) return;
	
	for (size_t i = 0; i < animationClips.size(); i++)
	{
		if (animationClips[i]->name == name)
		{
			SwitchAnimation(animationClips[i]);
			waitTillFinish = thisWaitTillFinish;
			return;
		}
	}
}

void Animator::SwitchAnimation(AnimationClip* newClip)
{
	lastAnimationClip = currentAnimationClip;
	currentAnimationClip = newClip;
	sprite = currentAnimationClip->sprite;
	scrRect.w = currentAnimationClip->animPixelWidth;
	scrRect.h = currentAnimationClip->textureHeight;
	currentFrame = 0;
}

void Animator::Update(float deltaTime)
{
	if (currentAnimationClip == nullptr) return;

	if (animationTimeCounter > currentAnimationClip->animSpeed)
	{
		scrRect.x = currentAnimationClip->animPixelWidth * currentFrame;
		scrRect.y = currentAnimationClip->animPixelHeight * (currentAnimationClip->currentRow - 1);
		
		if (currentFrame == currentAnimationClip->numberOfCells - 1 && !currentAnimationClip->loop)
		{
			waitTillFinish = false;
			//SwitchAnimation(lastAnimationClip);
		}

		for (size_t i = 0; i < currentAnimationClip->animationEvents.size(); i++)
		{
			if (currentFrame == currentAnimationClip->animationEvents[i].frame) currentAnimationClip->animationEvents[i].TriggerEvent();
		}

		if (currentFrame == 1) for (size_t i = 0; i < currentAnimationClip->animationEvents.size(); i++) currentAnimationClip->animationEvents[i].ResetEvent();

		currentFrame = (currentFrame + 1) % currentAnimationClip->numberOfCells;
		animationTimeCounter = 0;
	}
	else animationTimeCounter += deltaTime;
}

SDL_Rect& Animator::GetRect()
{
	return scrRect;
}
