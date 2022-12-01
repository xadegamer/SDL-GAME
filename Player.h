#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:

	Player();
	~Player();
	
	void Render();
	void Update();
	void Clean();
};

