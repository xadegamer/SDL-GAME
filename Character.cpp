#include "Character.h"

Character::Character()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetGravity(0);
	
	health = AddComponent<Health>();
	health->OnHealthChangeEvent = [=](float health) {OnHealthChange(health); };
	health->OnDeathEvent = [=]() {OnDeath(); };

	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);
	animator->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Pistol_Walk"), 8, 0.05);
	animator->AddAnimationClip("Hurt", AssetManager::GetSprite("CowBoy_6_Hurt"), 6, 0.05, false);
	animator->AddAnimationClip("Die", AssetManager::GetSprite("CowBoy_6_Die"), 6, 0.05, false);
	animator->AddAnimationClip("Attack", AssetManager::GetSprite("CowBoy_6_Pistol_Shoot"), 8, 0.03, false)->AddAnimationEvent("Shoot Event", 5, [=]() {OnShootEvent(); });
}

Character::~Character()
{
}

void Character::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->GetPosition(), transform->GetRotation(), animator->GetRect());
}