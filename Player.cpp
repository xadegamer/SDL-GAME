#include "Player.h"

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
