#include "Bullet.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction)
{	
	tag = Tag::BULLET;
	
	transform->SetPosition(startPosition + Camera::GetPosition());

	bulletType = type;
	
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetGravity(0);
	if (bulletType == BulletType::PLAYER) direction = GetDirectionToMouse(transform->GetPosition() - Camera::GetPosition());
	rigidBody->ApplyForce(direction * moveSpeed);

	circleCollider = AddComponent<CircleCollider>();
	circleCollider->isTrigger = true;
	
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight));

	//collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(50, 60));
	
	//transfrom->rotation = GetAngleFromMouse(transfrom->position, animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

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
	if (other->gameObject->CompareTag(Tag::ENEMY))
	{
		std::cout << "Bullet Hit Enemy" << std::endl;
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
