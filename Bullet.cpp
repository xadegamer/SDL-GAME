#include "Bullet.h"

#include "Health.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction)
{	
	tag = Tag::BULLET;
	
	transform->SetPosition(startPosition);

	bulletType = type;
	
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetGravity(0);

	rigidBody->ApplyForce(direction * moveSpeed);

	circleCollider = AddComponent<CircleCollider>();
	circleCollider->isTrigger = true;
	
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight));

	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
}


Bullet::~Bullet()
{

}

void Bullet::Update(float deltaTime)
{
	transform->Translate(rigidBody->GetPosition());
	animator->Update(deltaTime);
	rigidBody->Update(deltaTime);
	circleCollider->Update();

	if (IsOutSideScreen())
	{
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
		other->GetGameObject()->GetComponent<Health>()->TakeDamage(10);
		GameObject::Destroy(this);
	}
	else if (other->GetGameObject()->CompareTag(Tag::PLAYER) && bulletType == BulletType::ENEMY)
	{
		other->GetGameObject()->GetComponent<Health>()->TakeDamage(10);
		GameObject::Destroy(this);
	}
}

void Bullet::OnTriggerEnter(Collider* other)
{
	
}

bool Bullet::IsOutSideScreen()
{
	if (transform->GetPosition().x < 0 || transform->GetPosition().x > 1280 * 1.2 || transform->GetPosition().y < 0 || transform->GetPosition().y > 960 * 1.2)
	{
		return true;
	}
	return false;
}
