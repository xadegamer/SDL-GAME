#pragma once

#include "GameObject.h"


class Bullet : public GameObject
{
	
private:
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Animator* animator;
};

