#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

#include "AnimationControlledVfxEffect.h"

#include "TimedDelayVfxEffect.h"

#include "Money.h"

int Enemy::noOfEnemies;
int Enemy::numberOfEnemiesAlive;
std::function<void(int)> Enemy::OnAnyEnemyKilled = [](int) {};
std::function<void(int)> Enemy::OnAnyEnemyDespawned = [](int) {};

Enemy::Enemy(Vector2 position, float maxhealth) : Character(position)
{
	noOfEnemies++;
	numberOfEnemiesAlive = noOfEnemies;
	
	fireRate = 3;
	fireTimer = 0;
	despawnRate = 6;
	despawnTimer = 0;
	minAttackRange = 400;
	MaxAttackRange = 450;
	detectionRadius = 600;
	
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(SortingLayer::EnemyLayer);
	
	health->SetHealth(maxhealth);
	
	rigidBody->SetPosition(transform->GetPosition());
	
	spawnPoint = transform->GetPosition();
	
	currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);

	currentEnemyState = EnemyState::PATROL;
}

Enemy::~Enemy()
{
	noOfEnemies--; 
	if (OnAnyEnemyDespawned)OnAnyEnemyDespawned(noOfEnemies);
}

void Enemy::Update(float deltaTime)
{
	Character::Update(deltaTime);

	if (GetTarget() == nullptr) return;
	
	if (isDead)
	{
		EnemyDespawn();
		return;
	}
	
	animator->Update(deltaTime);
	
	if (!canMove) return;
	
	circleCollider->Update();

	switch (currentEnemyState)
	{
		case PATROL:
			PatrolState(deltaTime);
			break;
		case CHASE:
			ChaseState(deltaTime);
			break;
		case DEAD: break;
		default:break;
	}
}

void Enemy::OnCollisionEnter(Collider* other)
{
	if (other->GetGameObject()->CompareTag(Tag::ENEMY))
	{
		Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
		direction.normalize();
		transform->SetPosition(transform->GetPosition() += direction * 1.5);
	}
}

void Enemy::OnShootEvent()
{
	if (!canMove)
	{
		animator->ChangeAnimation("Die", true);
		return;
	}
	
	Vector2 spawnPosition = GetBulletSpawnLocation(circleCollider->GetCentre());
	Vector2 direction = MathUtility::GetDirectionToTarget(spawnPosition, target->GetComponent<Collider>()->GetCentre());
	SpawnBullet(spawnPosition, direction, BulletType::ENEMY);
}

void Enemy::OnTakeDamage()
{
	animator->ChangeAnimation("Hurt", true);
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("Hurt"), false);

	if (currentEnemyState == EnemyState::PATROL) currentEnemyState = EnemyState::CHASE;
}

void Enemy::OnDeath()
{
	currentEnemyState = EnemyState::DEAD;
	spriteRenderer->SetSortingOrder(SortingLayer::DeadCharacterLayer);
	canMove = false;
	circleCollider->SetIsEnabled(false);
	circleCollider->GetOnCollisionEnterEvent() = nullptr;
	animator->ChangeAnimation("Die", true);
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect("Kill"), false);
	GameObject::Instantiate(new TimedDelayVfxEffect(circleCollider->GetCentre(), "blood pool", SortingLayer::CharacterBloodLayer, 10));
	GameObject::Instantiate(new Money(circleCollider->GetCentre(), "Money", ColliderType::BOX, SortingLayer::CollectableLayer, 50));

	numberOfEnemiesAlive--;
	if (OnAnyEnemyKilled)OnAnyEnemyKilled(numberOfEnemiesAlive);
}

void Enemy::PatrolState(float deltaTime)
{
	if (MathUtility::DistanceBetweenTwoPoints(transform->GetPosition(), currentPatrolPoint) <= 5)
	{
		rigidBody->SetVelocity(Vector2(0, 0));
		currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);
	}
	else
	{
		transform->SetRotation(MathUtility::GetAngleFromTraget(transform->GetPosition() - circleCollider->GetCentre(), currentPatrolPoint - transform->GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth));
		animator->ChangeAnimation("Walk");
		rigidBody->MoveToPosition(currentPatrolPoint, 100, deltaTime);
		transform->SetPosition(rigidBody->GetPosition());
	}

	if (PlayerInRange(detectionRadius)) currentEnemyState = EnemyState::CHASE;
}

void Enemy::ChaseState(float deltaTime)
{
	transform->SetRotation(MathUtility::GetAngleFromTraget(transform->GetPosition(), GetTarget()->GetComponent<Collider>()->GetCentre(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth));

	if (fireTimer >= fireRate)
	{
		if (isDead || !canMove) return;
		animator->ChangeAnimation("Attack", true);
		fireTimer = 0;
	}
	else
	{
		if (!PlayerInRange(minAttackRange) && !PlayerInRange(MaxAttackRange))
		{
			animator->ChangeAnimation("Walk");
			rigidBody->MoveToPosition(GetTarget()->GetComponent<Transform>()->GetPosition(), 100, deltaTime);
			transform->SetPosition(rigidBody->GetPosition());
		}
		else
		{
			animator->ChangeAnimation("Idle");
		}
		
		fireTimer += Engine::GetDeltaTimer().getDeltaTime();
	}
}

void Enemy::EnemyDespawn()
{
	if (despawnTimer >= despawnRate)
	{
		GameObject::Destroy(this);
	}
	else despawnTimer += Engine::GetDeltaTimer().getDeltaTime();
}

bool Enemy::PlayerInRange(float range)
{
	return MathUtility::DistanceBetweenTwoPoints(circleCollider->GetCentre(), GetTarget()->GetComponent<Collider>()->GetCentre()) <= range;
}

GameObject* Enemy::GetTarget()
{
	if (target == nullptr) target = FindGameObjectWithTag(Tag::PLAYER);
	return target;
}
