
#include "Animator.h"

Animator::Animator()
{
	
}

Animator::~Animator()
{
	currentAnimationClip = nullptr;
}

void Animator::SetSpriteRender(SpriteRenderer* spriteRenderer)
{
	this->spriteRenderer = spriteRenderer;
}

void Animator::AddAnimationClip(std::string name , Sprite* sprite, int numberOfCells, float animSpeed)
{
	AnimationClip* animClip = new AnimationClip(name, sprite, numberOfCells, animSpeed);
	animationClips.push_back(animClip);
	if (currentAnimationClip == nullptr) SwitchAnimation(animClip);

	std::cout << "Added Clip" << std::endl;
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
	timeInAnimtionState = 0;
	currentAnimationClip = newClip;
	spriteRenderer->SetSprite(currentAnimationClip->sprite);
}

void Animator::Animate()
{
	timeInAnimtionState = SDL_GetTicks() / 1000.0f;
	
	int currentFrameIndex = (int)(timeInAnimtionState * currentAnimationClip->animSpeed) % currentAnimationClip->numberOfCells;
	
	scrRect.x = currentAnimationClip->animPixelWidth * currentFrameIndex;
	scrRect.y = currentAnimationClip->animPixelHeight * (currentAnimationClip->currentRow - 1);
	scrRect.w = currentAnimationClip->animPixelWidth;
	scrRect.h = currentAnimationClip->textureHeight;
}

SDL_Rect& Animator::GetRect()
{
	return scrRect;
}
