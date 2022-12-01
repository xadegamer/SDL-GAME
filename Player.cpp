#include "Player.h"

#include "MathUtility.h"

Player::Player()
{
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>();

	AddComponent<Animator>()->SetSpriteRender(renderer);

	Animator* anim = GetComponent<Animator>();

	anim->AddAnimationClip("Idle", AssetManager::GetSprite("Walk_riffle"), 6, 10);

	anim->AddAnimationClip("Fire",AssetManager::GetSprite("Riffle_Shot"), 9,  10, false)->AddAnimationEvent("Shoot Event", 5, []() {std::cout << "Shoot" << std::endl; });
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
	SetAngle(GetAngle(InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, position.x, position.y));
	
	if (InputManager::GetKey(SDL_SCANCODE_UP))
	{
		std::cout << "Up" << std::endl;
		position.y -= moveSpeed;
	}

	if (InputManager::GetKey(SDL_SCANCODE_DOWN))
	{
		std::cout << "Down" << std::endl;
		position.y += moveSpeed;
	}

	if (InputManager::GetKey(SDL_SCANCODE_LEFT))
	{
		std::cout << "Left" << std::endl;
		GetComponent<Animator>()->ChangeAnimation("Idle");
		position.x -= moveSpeed;
	}

	if (InputManager::GetKey(SDL_SCANCODE_RIGHT))
	{
		std::cout << "Right" << std::endl;
		position.x += moveSpeed;
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		GetComponent<Animator>()->ChangeAnimation("Fire");
	}
}

void Player::Clean()
{
}
