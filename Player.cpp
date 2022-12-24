#include "Player.h"

#include "Animator.h"

#include  "Game.h"

#include "Canvas.h"

#include "Slider.h"

#include "Engine.h"

Player::Player(Vector2 position, float maxhealth) : Character(position)
{
	tag = Tag::PLAYER;

	spriteRenderer->SetSortingOrder(SortingLayer::PlayerLayer);
	
	circleCollider = AddComponent<CircleCollider>(new CircleCollider);
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 2);
	circleCollider->GetOnCollisionEnterEvent() = [=](Collider* other) {OnCollisionEnter(other); };
	
	health->SetHealth(maxhealth);

	currentMoveSpeed = moveSpeed;

	animator->GetAnimationClipByName("Walk")->AddAnimationEvent("Foot Step Event 1", 2, [=]() {FootStep(); });
	animator->GetAnimationClipByName("Walk")->AddAnimationEvent("Foot Step Event 2", 6, [=]() {FootStep(); });
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	Character::Update(deltaTime);
	
	if (isDead) return;
	
	animator->Update(deltaTime);

	rigidBody->ResetForce();

	transform->SetRotation(MathUtility::GetAngleFromMouse(transform->GetPosition() - Camera::GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth) );

	//clamp player position to level bound with scale
	transform->SetXPosition(MathUtility::Clamp(transform->GetPosition().x, 0 - (animator->GetCurrentAnimationClip()->animPixelWidth / 2), Engine::LEVEL_WIDTH - (animator->GetCurrentAnimationClip()->animPixelWidth)) );
	transform->SetYPosition(MathUtility::Clamp(transform->GetPosition().y, 0 - (animator->GetCurrentAnimationClip()->animPixelHeight / 2), Engine::LEVEL_HEIGHT - (animator->GetCurrentAnimationClip()->animPixelHeight)) );

	if (!canMove) return;
	if (InputManager::GetKey(SDL_SCANCODE_W) == false && InputManager::GetKey(SDL_SCANCODE_S) == false && InputManager::GetKey(SDL_SCANCODE_A) == false && InputManager::GetKey(SDL_SCANCODE_D) == false)
	{
		animator->ChangeAnimation("Idle");
	}
	else
	{
		animator->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_W))
	{
		rigidBody->ApplyForceY(-currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_S))
	{
		rigidBody->ApplyForceY(currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_A))
	{
		rigidBody->ApplyForceX(-currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_D))
	{
		rigidBody->ApplyForceX(currentMoveSpeed);
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		animator->ChangeAnimation("Attack", true);
	}

	// if hold shift, increase move speed
	currentMoveSpeed = InputManager::GetKey(SDL_SCANCODE_LSHIFT) ? runSpeed : moveSpeed;
	
	circleCollider->Update();
	
	GameObject::Update(deltaTime);
}

void Player::LateUpdate(float deltaTime)
{
	if (isDead && !canMove) return;
	rigidBody->Update(deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Player::OnCollisionEnter(Collider* other)
{
	if (!other->IsTrigger())
	{
		Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
		direction.normalize();
		transform->SetPosition(transform->GetPosition() += direction * 1.8);
	}
}

void Player::OnShootEvent()
{
	if (!canMove)
	{
		animator->ChangeAnimation("Die", true);
		return;
	}
	Vector2 spawnPosition = GetBulletSpawnLocation(circleCollider->GetCentre());
	Vector2 direction = MathUtility::GetDirectionToMouse(spawnPosition - Camera::GetPosition());
	SpawnBullet(spawnPosition, direction, BulletType::PLAYER);
}

void Player::OnHealthChange(float currentHealth)
{
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Slider>("HealthSlider")->SetValue(currentHealth);
	UIManager::GetCanvasByID("GameMenu")->GetUIObjectByID<Slider>("HealthSlider")->SetText(std::to_string((int)(currentHealth * 100)) + "%");
}

void Player::OnTakeDamage()
{
	animator->ChangeAnimation("Hurt", true);
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("Hurt"), false);
}

void Player::OnHeal()
{
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("Heal"), false);
}

void Player::OnDeath()
{
	canMove = false;
	rigidBody->ResetForce();
	animator->ChangeAnimation("Die", true);	
}

void Player::OnDead()
{
	Character::OnDead();
	Engine::GetGame()->ChangeGameState(GameState::GameOver);
	UIManager::EnableCanvasByID("GameOverMenu");
}

void Player::FootStep()
{
	std::string soundName = "Player_Footstep_0";
	soundName += std::to_string(MathUtility::RandomRange(1, 4));
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect(soundName), false);
}
