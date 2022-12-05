#include "Player.h"

#include "MathUtility.h"

Player::Player()
{
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>();

	AddComponent<Animator>()->SetSpriteRender(renderer);

	Animator* anim = GetComponent<Animator>();

	anim->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle_A"), 11, 5);
	
	anim->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Walk"), 8, 10);

	anim->AddAnimationClip("Attack",AssetManager::GetSprite("CowBoy_6_Hurt"), 6,  10, false)->AddAnimationEvent("Shoot Event", 5, []() {std::cout << "Shoot" << std::endl; });

	AddComponent<RigidBody>()->gravity = 0;
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
	transfrom->rotation = GetAngleFromVector(InputManager::GetMousePosition() , transfrom->position);

	RigidBody* rigidBody = GetComponent<RigidBody>();
	rigidBody->ResetForce();
	transfrom->Translate(rigidBody->GetPosition());

	GetComponent<Animator>()->ChangeAnimation("Idle");

	if (InputManager::GetKey(SDL_SCANCODE_UP))
	{
		std::cout << "Up" << std::endl;
		rigidBody->ApplyForceY(-10);
		//transfrom->position.y -= moveSpeed;
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_DOWN))
	{
		std::cout << "Down" << std::endl;
		rigidBody->ApplyForceY(10);
		//transfrom->position.y += moveSpeed;
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_LEFT))
	{
		std::cout << "Left" << std::endl;
		rigidBody->ApplyForceX(-10);
		GetComponent<Animator>()->ChangeAnimation("Walk");
		//transfrom->position.x -= moveSpeed;
	}

	if (InputManager::GetKey(SDL_SCANCODE_RIGHT))
	{
		std::cout << "Right" << std::endl;
		rigidBody->ApplyForceX(10);
		//transfrom->position.x += moveSpeed;
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		GetComponent<Animator>()->ChangeAnimation("Attack");
	}

	rigidBody->Update(0.4f);
}

void Player::Clean()
{
}
