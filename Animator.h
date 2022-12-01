#pragma once
#include "Component.h"
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2.h"

#include "SpriteRenderer.h"

struct AnimationClip
{
public:
	
	std::string name;
	Sprite* sprite;
	
	int numberOfCells; //how many sprites are on the current row/state.
	int currentRow = 1; //which row on the spritesheet we want to go through.

	int textureHeight;
	int textureWidth;
	
	int animPixelHeight; //pixel height of a single animation frame.
	int animPixelWidth;//pixel width of a single animation frame.

	float animSpeed;//a multiplier for how fast to play the animation.

	AnimationClip (std::string name , Sprite* sprite, int numberOfCells, float animSpeed)
	{
		this->name = name;
		this->sprite = sprite;
		this->numberOfCells = numberOfCells;
		this->animSpeed = animSpeed;
		
		textureHeight = sprite->textureHeight;
		textureWidth = sprite->textureWidth;
		
		animPixelHeight = textureHeight;
		animPixelWidth = textureWidth / numberOfCells;
	}
};

class Animator : public Component
{
private:

	std::vector<AnimationClip*> animationClips;
	
	AnimationClip* currentAnimationClip;

	SpriteRenderer* spriteRenderer;

	SDL_Rect scrRect;

	float timeInAnimtionState; //this is used to calculate which frame of the animation should be shown depending on time
	
	void SwitchAnimation(AnimationClip* newClip);

public:
	
	Animator();
	~Animator();

	void SetSpriteRender(SpriteRenderer* spriteRenderer);

	void AddAnimationClip(std::string name ,Sprite* sprite, int numberOfCells, float animSpeed);

	void ChangeAnimation(std::string name);
	


	void Animate();

	SDL_Rect& GetRect();

	std::vector<AnimationClip*> GetAnimationClips() { return animationClips; }

	Sprite* GetSprite() { return currentAnimationClip->sprite; }
};
