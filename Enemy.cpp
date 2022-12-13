#include "Enemy.h"

Enemy::Enemy(Vector2 startPosition)
{
	transform->position = startPosition;
	
	tag = Tag::ENEMY;
	
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);

	boxCollider = AddComponent<BoxCollider>();

	boxCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(50, 60));

	boxCollider->OnCollisionEnterEvent = [=](Collider* other){OnCollisionEnter(other);};
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	animator->Update(deltaTime);
	boxCollider->Update();
}

void Enemy::OnCollisionEnter(Collider* other)
{
	transform->rotation = GetAngleFromTraget(transform->position - Camera::GetPosition(), other->GetPosition(), animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

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
