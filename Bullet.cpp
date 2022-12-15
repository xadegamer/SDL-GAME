#include "Bullet.h"

#include "Health.h"

#include "Game.h"

#include "GasCylinder.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction)
{	
	tag = Tag::BULLET;

	transform->SetPosition(startPosition);

	bulletType = type;
	
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(1);

	animator = AddComponent<Animator>(new Animator);
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>(new RigidBody);
	rigidBody->SetGravity(0);

	rigidBody->ApplyForce(direction * moveSpeed);

	circleCollider = AddComponent<CircleCollider>(new CircleCollider);
	circleCollider->isTrigger = true;
	
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight));

	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
}


Bullet::~Bullet()
{
	circleCollider->OnCollisionEnterEvent = nullptr;
}

void Bullet::Update(float deltaTime)
{
	transform->Translate(rigidBody->GetPosition());
	animator->Update(deltaTime);
	rigidBody->Update(deltaTime);
	circleCollider->Update();

	if (IsOutSideScreen())
	{
		isDestroyed = true;
		GameObject::Destroy(this);
	}
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
		Destroy(this);
	}
	else if (other->GetGameObject()->CompareTag(Tag::PLAYER) && bulletType == BulletType::ENEMY)
	{
		other->GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
		Destroy(this);
	}
	
	if (other->GetGameObject()->CompareTag(Tag::Gas_Cylinder))
	{
		GasCylinder* gasCylinder = dynamic_cast<GasCylinder*>(other->GetGameObject());
		if (gasCylinder) gasCylinder->Explosion();
		Destroy(this);
	}
}

bool Bullet::IsOutSideScreen()
{
	if (transform->GetPosition().x < 0 || transform->GetPosition().x > LEVEL_WIDTH || transform->GetPosition().y < 0 || transform->GetPosition().y > LEVEL_HEIGHT)
	{
		return true;
	}
	return false;
}
