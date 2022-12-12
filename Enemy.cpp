#include "Enemy.h"

Enemy::Enemy(Vector2 startPosition)
{
	tag = Tag::ENEMY;
	
	transform->position = startPosition;
	
	spriteRenderer = AddComponent<SpriteRenderer>();
	
	rigidBody = AddComponent<RigidBody>();
	
	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);

	collider = AddComponent<Collider>();

	collider->SetUp(Box, transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(50, 60));
	
	//collider->SetUp(Circle, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(90, 120));
	//collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(0, 0));
	
	collider->AssignCollisonCallBack([](Collider* other)
	{
			if (other->gameObject->CompareTag(Tag::BULLET))
			{
				std::cout << "Enemy Take Damage" << std::endl;
			}

			if (other->gameObject->CompareTag(Tag::PLAYER))
			{
				std::cout <<"Player collide with enemy" << std::endl;
			}
	});

}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	animator->Update(deltaTime);
	collider->Update();
}

void Enemy::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->position, transform->rotation, animator->GetRect());
}
