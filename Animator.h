#pragma once
#include "Component.h"
#include "SpriteRenderer.h"

#include <string>


#include <iostream>
#include "Vector2.h"

#include <map>
#include "SDL.h"
#include <vector>
#include <stdio.h>


struct AnimationEvent
{
	std::string eventName;
	int frame;
	void (*eventLogic)();
	bool isFired;

	AnimationEvent(std::string eventName, int frame, void (*eventLogic)())
	{
		this->eventName = eventName;
		this->frame = frame;
		this->eventLogic = eventLogic;
	}

	void TriggerEvent()
	{
		if (!isFired)
		{
			eventLogic();
			isFired = true;
		}
	}

	void ResetEvent()
	{
		if(isFired) isFired = false;
	}
};

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

	bool loop;

	std::vector<AnimationEvent> animationEvents;


	AnimationClip (std::string name , Sprite* sprite, int numberOfCells, float animSpeed, bool loop = true)
	{
		this->name = name;
		this->sprite = sprite;
		this->numberOfCells = numberOfCells;
		this->animSpeed = animSpeed;
		this->loop = loop;
		
		textureHeight = sprite->textureHeight;
		textureWidth = sprite->textureWidth;
		
		animPixelHeight = textureHeight;
		animPixelWidth = textureWidth / numberOfCells;
	}

	void AddAnimationEvent(std::string eventName, int frame, void (*eventLogic)())
	{
		animationEvents.push_back(AnimationEvent(eventName, frame, eventLogic));
	}
};

struct AnimationTransition
{
	std::string name;
	std::string from;
	std::string to;
	float duration;
	float timeInTransition;
	bool isPlaying = false;
	bool isFinished = false;

	AnimationTransition(std::string name, std::string from, std::string to, float duration)
	{
		this->name = name;
		this->from = from;
		this->to = to;
		this->duration = duration;
	}
};

class Animator : public Component
{
private:

	bool waitTillFinish;

	std::vector<AnimationClip*> animationClips;
	
	AnimationClip* currentAnimationClip;

	AnimationClip* lastAnimationClip;

	Sprite* sprite;

	SDL_Rect scrRect;

	float animationTimeCounter;
	
	int currentFrame; //this is used to calculate which frame of the animation should be shown depending on time
	
	void SwitchAnimation(AnimationClip* newClip);

public:
	
	Animator();
	~Animator();

	void SetSprite(Sprite* spriteRendererSprite);

	AnimationClip* AddAnimationClip(std::string name, Sprite* sprite, int numberOfCells, float animSpeed, bool loop = true);

	void ChangeAnimation(std::string name, bool waitTillFinish = false);

	void Update(float deltaTime);

	SDL_Rect& GetRect();

	std::vector<AnimationClip*> GetAnimationClips() { return animationClips; }
	
	AnimationClip* GetCurrentAnimationClip() { return currentAnimationClip; }

	Sprite* GetSprite() { return currentAnimationClip->sprite; }
};
