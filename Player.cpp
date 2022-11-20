#include "Player.h"

Player::Player()
{
	Load(0, 0, "Player");
}

Player::~Player()
{
	
}

void Player::Load(int x, int y, std::string textureID)
{
	GameObject::Load(x, y, textureID);
}

void Player::Render(SDL_Renderer* pRenderer)
{
	GameObject::Render(pRenderer);
}

void Player::Update()
{
	
}

void Player::Clean()
{
}
