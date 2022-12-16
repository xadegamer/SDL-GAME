#include "Character.h"

Character::Character(Vector2 position) : GameObject(position)
{
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	animator = AddComponent<Animator>(new Animator);
	animator->SetSprite(spriteRenderer->GetSprite());
	rigidBody = AddComponent<RigidBody>(new RigidBody);
	rigidBody->SetGravity(0);
	
	health = AddComponent<HealthComponent>(new HealthComponent);
	health->OnHealthChangeEvent = [=](float health) {OnHealthChange(health); };
	health->OnTakeDamageEvent = [=]() {OnTakeDamage(); };
	health->OnHealEvent = [=]() {OnHeal(); };
	health->OnDeathEvent = [=]() {OnDeath(); };

	animator->AddAnimationClip("Idle", AssetManager::GetSprite("CowBoy_6_Idle"), 11, 0.05);
	animator->AddAnimationClip("Walk", AssetManager::GetSprite("CowBoy_6_Pistol_Walk"), 8, 0.05);
	animator->AddAnimationClip("Hurt", AssetManager::GetSprite("CowBoy_6_Hurt"), 6, 0.01, false);
	animator->AddAnimationClip("Die", AssetManager::GetSprite("CowBoy_6_Die"), 5, 0.05, false)->AddAnimationEvent("Shoot Event", 4, [=]() {OnDead(); });
	animator->AddAnimationClip("Attack", AssetManager::GetSprite("CowBoy_6_Pistol_Shoot"), 8, 0.02, false)->AddAnimationEvent("Shoot Event", 5, [=]() {OnShootEvent(); });
}

Character::~Character()
{
	health->OnHealthChangeEvent = nullptr;
	health->OnTakeDamageEvent = nullptr;
	health->OnHealEvent = nullptr;
	health->OnDeathEvent = nullptr;
}

void Character::Update(float deltatime)
{
	GameObject::Update(deltatime);
}

void Character::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->GetPosition(), transform->GetRotation(), animator->GetRect());
}

void Character::OnDead()
{
	isDead = true;
}

Vector2 Character::GetBulletSpawnLocation(Vector2 playerPos)
{
	float offsetX = 10;
	float offsetY = -80;
	double theta = transform->GetRotation() * (M_PI / 180);
	Vector2 spawnPosition = Vector2(playerPos.x + offsetX * cos(theta) - offsetY * sin(theta), playerPos.y + offsetX * sin(theta) + offsetY * cos(theta));
	return spawnPosition;
}

void Character::SpawnBullet(Vector2 spawnPos, Vector2 direction, BulletType bulletType)
{
	Bullet* bullet = new Bullet(spawnPos, bulletType, direction);
}
