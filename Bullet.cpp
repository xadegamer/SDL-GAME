#include "Bullet.h"

#include "HealthComponent.h"

#include "Game.h"

#include "GasCylinder.h"

#include "AnimationControlledVfxEffect.h"

#include "Engine.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction) : GameObject(startPosition)
{	
	tag = Tag::BULLET;

	bulletType = type;
	
	moveSpeed = 500;
	
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(1);

	animator = AddComponent<Animator>(new Animator);
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>(new RigidBody);
	rigidBody->SetGravity(0);

	rigidBody->ApplyForce(direction * moveSpeed);

	circleCollider = AddComponent<CircleCollider>(new CircleCollider);
	circleCollider->SetTrigger(true);
	
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight));

	circleCollider->GetOnCollisionEnterEvent() = [=](Collider* other) {OnCollisionEnter(other); };
}


Bullet::~Bullet()
{
	circleCollider->GetOnCollisionEnterEvent() = nullptr;
}

void Bullet::Update(float deltaTime)
{
	transform->Translate(rigidBody->GetPosition());
	animator->Update(deltaTime);
	rigidBody->Update(deltaTime);
	circleCollider->Update();

	if (IsOutSideScreen() && !IsToBeDestroyed())
	{
		RemoveBullet();
	}

	GameObject::Update(deltaTime);
}

void Bullet::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->GetPosition(), transform->GetRotation(), animator->GetRect());
}

void Bullet::OnCollisionEnter(Collider* other)
{
	if (other->GetGameObject()->CompareTag(Tag::ENEMY) && bulletType == BulletType::PLAYER)
	{
		other->GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
		RemoveBullet();
	}
	else if (other->GetGameObject()->CompareTag(Tag::PLAYER) && bulletType == BulletType::ENEMY)
	{
		other->GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
		RemoveBullet();
	}
	else if (other->GetGameObject()->CompareTag(Tag::GAS_CYLINDER))
	{
		GasCylinder* gasCylinder = dynamic_cast<GasCylinder*>(other->GetGameObject());
		if (gasCylinder) gasCylinder->Explosion();
		RemoveBullet();
	}
	else if (other->GetGameObject()->CompareTag(Tag::DEFAULT)) RemoveBullet();
}

bool Bullet::IsOutSideScreen()
{
	if (transform->GetPosition().x < 0 || transform->GetPosition().x > Engine::LEVEL_WIDTH || transform->GetPosition().y < 0 || transform->GetPosition().y > Engine::LEVEL_HEIGHT)
	{
		return true;
	}
	return false;
}

void Bullet::RemoveBullet()
{
	Instantiate<AnimationControlledVfxEffect>(new AnimationControlledVfxEffect(circleCollider->GetPosition(), "BulletHit", 5, SortingLayer::VfxLayer));
	GameObject::Destroy(this);
}
