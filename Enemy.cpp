#include "Enemy.h"

Enemy::Enemy(Vector2 startPosition)
{
	transfrom->position = startPosition;
	
	spriteRenderer = AddComponent<SpriteRenderer>();
	
	rigidBody = AddComponent<RigidBody>();
	
	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);

	collider = AddComponent<Collider>();
	
	collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(50, 60));
	//collider->SetUp(Circle, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2), Vector2(90, 120));
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
	spriteRenderer->Draw(animator->GetSprite()->texture, transfrom->position, transfrom->rotation, animator->GetRect());
}
