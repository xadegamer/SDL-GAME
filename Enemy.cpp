#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

#include "VfxEffect.h"

Enemy::Enemy(Vector2 position, float maxhealth) : Character(position)
{
	fireRate = 3;
	fireTimer = 0;
	despawnRate = 6;
	despawnTimer = 0;
	attackRange = 400;
	detectionRadius = 600;
	
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(1);

	circleCollider = AddComponent<CircleCollider>(new CircleCollider);
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), 2);
	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
	
	health->SetHealth(maxhealth);
	
	rigidBody->SetPosition(transform->GetPosition());
	
	spawnPoint = transform->GetPosition();
	
	currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);

	currentEnemyState = EnemyState::PATROL;
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
	//if (!other->isTrigger)
	//{
	//	Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
	//	direction.normalize();
	//	transform->SetPosition(transform->GetPosition() += direction * 1.5);
	//}
}

void Enemy::OnShootEvent()
{
	if (!canMove)
	{
		OnDeath();
		return;
	}
	
	Vector2 spawnPosition = GetBulletSpawnLocation(circleCollider->GetCentre());
	Vector2 direction = MathUtility::GetDirectionToTarget(spawnPosition, Game::player->GetComponent<Collider>()->GetCentre());
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
//	Instantiate<VfxEffect>(new VfxEffect("blood pool", 1), circleCollider->GetPosition());
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
	transform->SetRotation(MathUtility::GetAngleFromTraget(transform->GetPosition(), Game::player->GetComponent<Collider>()->GetCentre(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth));

	if (fireTimer >= fireRate)
	{
		if (!isDead) animator->ChangeAnimation("Attack", true);
		fireTimer = 0;
	}
	else
	{
		if (!PlayerInRange(attackRange))
		{
			animator->ChangeAnimation("Walk");
			rigidBody->MoveToPosition(Game::player->GetComponent<Transform>()->GetPosition(), 100, deltaTime);
			transform->SetPosition(rigidBody->GetPosition());
		}
		else
		{
			animator->ChangeAnimation("Idle");
		}
		
		fireTimer += Engine::deltaTimer.getDeltaTime();
	}
}

void Enemy::EnemyDespawn()
{
	if (despawnTimer >= despawnRate)
	{
		Destroy(this);
	}
	else despawnTimer += Engine::deltaTimer.getDeltaTime();
}

bool Enemy::PlayerInRange(float range)
{
	std::cout << "Player In Range: " << MathUtility::DistanceBetweenTwoPoints(circleCollider->GetCentre(), Game::player->GetComponent<Collider>()->GetCentre()) << std::endl;
	return MathUtility::DistanceBetweenTwoPoints(circleCollider->GetCentre(), Game::player->GetComponent<Collider>()->GetCentre()) <= range;
}
