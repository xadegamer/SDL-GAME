#include "Player.h"

#include "Animator.h"

Player::Player()
{
	tag = Tag::PLAYER;
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);
	animator->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Pistol_Walk"), 8, 0.05);
	animator->AddAnimationClip("Attack",AssetManager::GetSprite("CowBoy_6_Pistol_Shoot"), 8, 0.03, false)->AddAnimationEvent("Shoot Event", 5,
		[]() {std::cout << "Spawn Bullet" << std::endl; AudioManager::PlaySoundEffect(AssetManager::GetSound("Mix_Chunk"), false);});
	
	rigidBody = AddComponent<RigidBody>();
	rigidBody->gravity = 0;

	collider = AddComponent<Collider>();


	collider->SetUp(Circle, transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(90, 120));
	
	//collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(50, 60));

	//collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(0, 0));
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	transform->rotation = GetAngleFromMouse(transform->position - Camera::GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

	transform->Translate(rigidBody->GetPosition());

	animator->Update(deltaTime);

	if (InputManager::GetKey(SDL_SCANCODE_W) == false && InputManager::GetKey(SDL_SCANCODE_S) == false && InputManager::GetKey(SDL_SCANCODE_A) == false && InputManager::GetKey(SDL_SCANCODE_D) == false)
	{
		rigidBody->ResetForce();
		animator->ChangeAnimation("Idle");
	}

	if (InputManager::GetKey(SDL_SCANCODE_W))
	{
		rigidBody->ApplyForceY(-moveSpeed);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_S))
	{
		rigidBody->ApplyForceY(moveSpeed);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_A))
	{
		rigidBody->ApplyForceX(-moveSpeed);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_D))
	{
		rigidBody->ApplyForceX(moveSpeed);
		GetComponent<Animator>()->ChangeAnimation("Walk");
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		GetComponent<Animator>()->ChangeAnimation("Attack", true);
	}

	rigidBody->Update(deltaTime);
}

void Player::Draw(Vector2 cameraPos)
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->position - cameraPos, transform->rotation, animator->GetRect());
}
