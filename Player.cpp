#include "Player.h"

#include "MathUtility.h"

Player::Player()
{
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SpriteRendererSprite(spriteRenderer->GetSprite());
	animator = GetComponent<Animator>();
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 5);
	animator->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Pistol_Walk"), 8, 10);
	animator->AddAnimationClip("Attack",AssetManager::GetSprite("CowBoy_6_Pistol_Shoot"), 8,  10, false)->AddAnimationEvent("Shoot Event", 5, []() {std::cout << "Shoot" << std::endl; });
	
	rigidBody = AddComponent<RigidBody>();
	rigidBody->gravity = 0;
}

Player::~Player()
{
	
}


void Player::Update()
{
	transfrom->rotation = GetAngleFromMouse(transfrom->position, animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

	rigidBody->ResetForce();
	transfrom->Translate(rigidBody->GetPosition());

	if (InputManager::GetKey(SDL_SCANCODE_W) == false && InputManager::GetKey(SDL_SCANCODE_S) == false && InputManager::GetKey(SDL_SCANCODE_A) == false && InputManager::GetKey(SDL_SCANCODE_D) == false)
	{
		animator->ChangeAnimation("Idle");
		transfrom->Translate(rigidBody->GetPosition());
	}

	if (InputManager::GetKey(SDL_SCANCODE_W))
	{
		rigidBody->ApplyForceY(-10);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_S))
	{
		rigidBody->ApplyForceY(10);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_A))
	{
		rigidBody->ApplyForceX(-10);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_D))
	{
		rigidBody->ApplyForceX(10);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		std::cout << "Added Shoot" << std::endl;
		GetComponent<Animator>()->ChangeAnimation("Attack", true);
	}

	rigidBody->Update(0.4f);
}

void Player::Draw()
{
	animator->Animate();

	spriteRenderer->Draw(animator->GetSprite()->texture, transfrom->position, transfrom->rotation, animator->GetRect());
}
