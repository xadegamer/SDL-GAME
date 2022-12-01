#include "Player.h"

Player::Player()
{
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>();

	AddComponent<Animator>()->SetSpriteRender(renderer);

	Animator* anim = GetComponent<Animator>();

	anim->AddAnimationClip("Walk_firethrower", AssetManager::GetSprite("Walk_firethrower"), 6, 10);

	anim->AddAnimationClip("FlameThrower",AssetManager::GetSprite("FlameThrower"), 9, 10);
}

Player::~Player()
{
	
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Update()
{
	
}

void Player::Clean()
{
}
