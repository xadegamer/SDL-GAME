#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:

	Player();
	~Player();
	
	void Load(int x, int y, std::string textureID);
	void Render(SDL_Renderer* pRenderer);
	void Update();
	void Clean();
};

