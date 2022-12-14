#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 startPosition, float maxhealth)
{
	transform->SetPosition(startPosition);
	
	tag = Tag::ENEMY;

	boxCollider = AddComponent<BoxCollider>();
	//boxCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(50, 60));
	boxCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight));
	boxCollider->OnCollisionEnterEvent = [=](Collider* other){OnCollisionEnter(other);};

	//circleCollider = AddComponent<CircleCollider>();
	//circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 2);
	//circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	animator->Update(deltaTime);
	boxCollider->Update();

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

void Enemy::OnTriggerEnter(Collider* other)
{
	
}

void Enemy::OnShootEvent()
{
	Vector2 spawnPosition = GetBulletSpawnLocation(boxCollider->GetCentre());
	Vector2 direction = GetDirectionToTarget(spawnPosition, Game::player->GetComponent<Collider>()->GetCentre());
	SpawnBullet(spawnPosition, direction, BulletType::ENEMY);
}

void Enemy::OnTakeDamage()
{
}

void Enemy::OnDeath()
{
}

void Enemy::Patrol()
{
	if (fireTimer >= fireRate)
	{
		GetComponent<Animator>()->ChangeAnimation("Attack", true);
		fireTimer = 0;
	}
	else fireTimer += Engine::deltaTimer.getDeltaTime();
}
