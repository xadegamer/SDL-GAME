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
	circleCollider->Update();

	transform->SetRotation( GetAngleFromTraget(transform->GetPosition() - Camera::GetPosition(), Game::player->GetComponent<Collider>()->GetCentre(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth) );
	animator->ChangeAnimation("Idle");
	Patrol();
}

void Enemy::OnCollisionEnter(Collider* other)
{
	if (other->gameObject->CompareTag(Tag::BULLET))
	{
		std::cout << "Enemy Take Damage" << std::endl;
	}

	if (other->gameObject->CompareTag(Tag::PLAYER))
	{
		std::cout << "Player collide with enemy" << std::endl;
	}
}

void Enemy::OnTriggerEnter(Collider* other)
{
	
}

void Enemy::OnShootEvent()
{
	Vector2 direction = GetDirectionToTarget(circleCollider->GetCentre(), Game::player->GetComponent<Collider>()->GetCentre());
	std::cout << "Enemy Shoot: Position: " << circleCollider->GetCentre() << "Centre: " << direction << std::endl;

	Game::SpawnBullet(circleCollider->GetCentre(), BulletType::ENEMY, direction);
}

void Enemy::Patrol()
{
	if (fireTimer >= fireRate)
	{
		GetComponent<Animator>()->ChangeAnimation("Attack", true);
		fireTimer = 0;
	}
	else
	{
		fireTimer += Engine::deltaTimer.getDeltaTime();
	}
}
