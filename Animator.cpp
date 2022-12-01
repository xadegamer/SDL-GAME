
#include "Animator.h"

Animator::Animator()
{
	
}

Animator::~Animator()
{
	currentAnimationClip = nullptr;
	lastAnimationClip = nullptr;
}

void Animator::SetSpriteRender(SpriteRenderer* spriteRenderer)
{
	this->spriteRenderer = spriteRenderer;
}

AnimationClip* Animator::AddAnimationClip(std::string name, Sprite* sprite, int numberOfCells, float animSpeed, bool loop)
{
	AnimationClip* animClip = new AnimationClip(name, sprite, numberOfCells, animSpeed, loop);
	animationClips.push_back(animClip);
	if (currentAnimationClip == nullptr) SwitchAnimation(animClip);
	std::cout << "Added Clip" << std::endl;
	return animClip;
}

void Animator::ChangeAnimation(std::string name)
{
	for (size_t i = 0; i < animationClips.size(); i++)
	{
		if (animationClips[i]->name == name)
		{
			SwitchAnimation(animationClips[i]);
			return;
		}
	}
}

void Animator::SwitchAnimation(AnimationClip* newClip)
{
	if (currentAnimationClip != nullptr && currentAnimationClip->name == newClip->name) return;

	isChanging = true;
	
	std::cout << "Reset Animation" << std::endl;
	
	lastAnimationClip = currentAnimationClip;
	currentAnimationClip = newClip;
	spriteRenderer->SetSprite(currentAnimationClip->sprite);

	timeInAnimtionState = 0;
	currentFrame = 0;

	isChanging = false;

	std::cout << "Switched Animation" << std::endl;
}

void Animator::Animate()
{
	if (currentAnimationClip == nullptr || isChanging) return;
	
	timeInAnimtionState = SDL_GetTicks() / 1000.0f;
	
	currentFrame = (int)(timeInAnimtionState * currentAnimationClip->animSpeed) % currentAnimationClip->numberOfCells;

	if (currentAnimationClip->name == "Fire")
	std::cout << currentFrame << std::endl;

	if (currentFrame == currentAnimationClip->numberOfCells - 1 && !currentAnimationClip->loop)
	{ 
		isChanging = true;
		std::cout << "Animation Finished" << std::endl;
		SwitchAnimation(lastAnimationClip);
	}


	scrRect.x = currentAnimationClip->animPixelWidth * currentFrame;
	scrRect.y = currentAnimationClip->animPixelHeight * (currentAnimationClip->currentRow - 1);
	scrRect.w = currentAnimationClip->animPixelWidth;
	scrRect.h = currentAnimationClip->textureHeight;

	// Call anim event
	for (size_t i = 0; i < currentAnimationClip->animationEvents.size(); i++)
	{
		if (currentFrame == currentAnimationClip->animationEvents[i].frame)
		{
			currentAnimationClip->animationEvents[i].TriggerEvent();
		}
	}

	//ResetEvent
	if (currentFrame == 1)
	{
		for (size_t i = 0; i < currentAnimationClip->animationEvents.size(); i++) currentAnimationClip->animationEvents[i].ResetEvent();
	}
}

SDL_Rect& Animator::GetRect()
{
	return scrRect;
}
