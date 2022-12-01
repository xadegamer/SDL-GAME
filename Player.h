#pragma once
#include "GameObject.h"
#include "InputManager.h"


class Player : public GameObject
{
private:
	float moveSpeed = 3.0f;
	
public:

	Player();
	~Player();
	
	void Render();
	void Update();
	void Clean();
};

