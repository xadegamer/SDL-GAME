#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 startPosition, float maxhealth)
{
	transform->SetPosition(startPosition);
	
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(1);

	//boxCollider = AddComponent<BoxCollider>();
	//boxCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 0.5f);
	//boxCollider->OnCollisionEnterEvent = [=](Collider* other){OnCollisionEnter(other);};

	circleCollider = AddComponent<CircleCollider>();
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 2);
	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
	
	health->SetHealth(maxhealth);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	if (isDead)
	{
		EnemyDespawn();
		return;
	}
	
	animator->Update(deltaTime);
	
	if (!canMove) return;
	
	circleCollider->Update();

	//transform->SetRotation( GetAngleFromTraget(transform->GetPosition() - Camera::GetPosition(), Game::player->GetComponent<Collider>()->GetCentre(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth) );
	transform->SetRotation(GetAngleFromTraget(transform->GetPosition(), Game::player->GetComponent<Collider>()->GetCentre(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth));
	animator->ChangeAnimation("Idle");
	Patrol();
}

void Enemy::OnCollisionEnter(Collider* other)
{
	if (other->GetGameObject()->CompareTag(Tag::BULLET))
	{
		std::cout << "Enemy Take Damage" << std::endl;
	}

	if (other->GetGameObject()->CompareTag(Tag::PLAYER))
	{
		std::cout << "Player collide with enemy" << std::endl;
	}
}

void Enemy::OnShootEvent()
{
	Vector2 spawnPosition = GetBulletSpawnLocation(circleCollider->GetCentre());
	Vector2 direction = GetDirectionToTarget(spawnPosition, Game::player->GetComponent<Collider>()->GetCentre());
	SpawnBullet(spawnPosition, direction, BulletType::ENEMY);
	AudioManager::PlaySoundEffect(AssetManager::GetSound("Mix_Chunk"), false);
}

void Enemy::OnTakeDamage()
{
	std::cout << "Enemy Take Damage" << std::endl;
	animator->ChangeAnimation("Hurt", true);
}

void Enemy::OnDeath()
{
	canMove = false;
	circleCollider->SetIsEnabled(false);
	circleCollider->OnCollisionEnterEvent = nullptr;
	animator->ChangeAnimation("Die", true);
}

void Enemy::Patrol()
{
	if (fireTimer >= fireRate)
	{
		animator->ChangeAnimation("Attack", true);
		fireTimer = 0;
	}
	else fireTimer += Engine::deltaTimer.getDeltaTime();
}

void Enemy::EnemyDespawn()
{
	if (despawnTimer >= despawnRate)
	{
		Destroy(this);
	}
	else despawnTimer += Engine::deltaTimer.getDeltaTime();
}