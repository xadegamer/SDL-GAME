#include "Player.h"

#include "Animator.h"

#include  "Game.h"

Player::Player(Vector2 startPosition)
{
	transform->position = startPosition;
	
	tag = Tag::PLAYER;

	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);
	animator->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Pistol_Walk"), 8, 0.05);
	animator->AddAnimationClip("Attack", AssetManager::GetSprite("CowBoy_6_Pistol_Shoot"), 8, 0.03, false)->AddAnimationEvent("Shoot Event", 5, [=]() {OnShootEvent(); });

	circleCollider = AddComponent<CircleCollider>();
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(90, 120));
	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	transform->rotation = GetAngleFromMouse(transform->position - Camera::GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

	transform->Translate(rigidBody->GetPosition());

	animator->Update(deltaTime);

	//clamp player position to level bound with scale
	 transform->position.x = Clamp(transform->position.x, 0 - (animator->GetCurrentAnimationClip()->animPixelWidth / 2), 1280 + (animator->GetCurrentAnimationClip()->animPixelWidth / 2));
	 transform->position.y = Clamp(transform->position.y, 0 - (animator->GetCurrentAnimationClip()->animPixelHeight / 2), 960 + (animator->GetCurrentAnimationClip()->animPixelHeight / 2));
	
	////Left and Right
	//if ((transform->position.x < 0) transform->position.x = 0; else if (transform->position.x > 1280) transform->position.x = 1280;
	////Top and Bottom
	//if (transform->position.y < 0) transform->position.y = 0; else if (transform->position.y > 960)transform->position.y = 960;

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

	circleCollider->Update();
}

void Player::OnCollisionEnter(Collider* other)
{
	
}

void Player::OnTriggerEnter(Collider* other)
{
	
}

void Player::OnShootEvent()
{
	Game::SpawnBullet(circleCollider->GetPosition(), BulletType::PLAYER);
	std::cout << "Spawn Bullet" << std::endl; AudioManager::PlaySoundEffect(AssetManager::GetSound("Mix_Chunk"), false);
}
