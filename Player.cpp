#include "Player.h"

#include "Animator.h"

#include  "Game.h"

#include "Canvas.h"

#include "Slider.h"

Player::Player(Vector2 startPosition, float maxhealth)
{
	transform->SetPosition(startPosition);
	
	tag = Tag::PLAYER;

	spriteRenderer->SetSortingOrder(2);
	
	circleCollider = AddComponent<CircleCollider>();
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 2);
	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
	
	health->SetHealth(maxhealth);
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	if (isDead) return;
	animator->Update(deltaTime);

	transform->SetRotation( GetAngleFromMouse(transform->GetPosition() - Camera::GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth) );


	//clamp player position to level bound with scale
	 transform->SetXPosition( Clamp(transform->GetPosition().x, 0 - (animator->GetCurrentAnimationClip()->animPixelWidth / 2), 1280 + (animator->GetCurrentAnimationClip()->animPixelWidth / 2)) );
	 transform->SetYPosition( Clamp(transform->GetPosition().y, 0 - (animator->GetCurrentAnimationClip()->animPixelHeight / 2), 960 + (animator->GetCurrentAnimationClip()->animPixelHeight / 2)) );
	
	////Left and Right
	//if ((transform->position.x < 0) transform->position.x = 0; else if (transform->position.x > 1280) transform->position.x = 1280;
	////Top and Bottom
	//if (transform->position.y < 0) transform->position.y = 0; else if (transform->position.y > 960)transform->position.y = 960;

	 if (!canMove) return;
	if (InputManager::GetKey(SDL_SCANCODE_W) == false && InputManager::GetKey(SDL_SCANCODE_S) == false && InputManager::GetKey(SDL_SCANCODE_A) == false && InputManager::GetKey(SDL_SCANCODE_D) == false)
	{
		rigidBody->ResetForce();
		animator->ChangeAnimation("Idle");
	}

	if (InputManager::GetKey(SDL_SCANCODE_W))
	{
		rigidBody->ApplyForceY(-moveSpeed);
		animator->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_S))
	{
		rigidBody->ApplyForceY(moveSpeed);
		animator->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_A))
	{
		rigidBody->ApplyForceX(-moveSpeed);
		animator->ChangeAnimation("Walk");
	}

	if (InputManager::GetKey(SDL_SCANCODE_D))
	{
		rigidBody->ApplyForceX(moveSpeed);
		animator->ChangeAnimation("Walk");
	}

	if (InputManager::GetMouseButtonDown(InputManager::LEFT))
	{
		animator->ChangeAnimation("Attack", true);
	}
	
	circleCollider->Update();
}

void Player::LateUpdate(float deltaTime)
{
	if (isDead && !canMove) return;
	rigidBody->Update(deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Player::OnCollisionEnter(Collider* other)
{
	if (!other->isTrigger)
	{
		Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
		direction.normalize();
		transform->SetPosition(transform->GetPosition() += direction * 1.5);
	}
}

void Player::OnShootEvent()
{
	Vector2 spawnPosition = GetBulletSpawnLocation(circleCollider->GetCentre());
	Vector2 direction = GetDirectionToMouse(spawnPosition - Camera::GetPosition());
	SpawnBullet(spawnPosition, direction, BulletType::PLAYER);

	AudioManager::PlaySoundEffect(AssetManager::GetSound("Mix_Chunk"), false);
}

void Player::OnHealthChange(float currentHealth)
{
	Canvas* GameCanvas = UIManager::GetCanvasByID("GameMenu");	
	if (GameCanvas != nullptr)
	{
		UIObject* sliderObj = GameCanvas->GetUIObjectByID("HealthSlider");
		if (!sliderObj) return;
		Slider* slider = dynamic_cast<Slider*>(sliderObj);
		if (!slider) return;
		slider->SetValue(currentHealth);

		//remove decima
		std::string healthString = std::to_string(health->GetHealth());
		healthString = healthString.substr(0, healthString.find("."));
		slider->SetText(healthString);
	}
}

void Player::OnTakeDamage()
{
	animator->ChangeAnimation("Hurt", true);
}

void Player::OnHeal()
{
	
}

void Player::OnDeath()
{
	canMove = false;
	animator->ChangeAnimation("Die", true);	
}

void Player::OnDead()
{
	Character::OnDead();
	Game::ChangeGameState(GameState::GameOver);
	UIManager::EnableCanvasByID("GameOverMenu");
}
