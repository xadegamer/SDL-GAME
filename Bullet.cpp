#include "Bullet.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction)
{	
	tag = Tag::BULLET;
	
	transform->position = startPosition + Camera::GetPosition();

	bulletType = type;
	
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>();
	rigidBody->gravity = 0;
	if (bulletType == BulletType::PLAYER) direction = GetDirectionToMouse(transform->position - Camera::GetPosition() );
	rigidBody->ApplyForce(direction * moveSpeed);

	circleCollider = AddComponent<CircleCollider>();
	
	circleCollider->SetUp(transform, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(7, 10));

	//collider->SetUp(Box, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(50, 60));
	
	//transfrom->rotation = GetAngleFromMouse(transfrom->position, animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

	circleCollider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
}


Bullet::~Bullet()
{
	std::cout << "Bullet Removed" << endl;
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
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->position, transform->rotation, animator->GetRect());
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
	if (transform->position.x < 0 || transform->position.x > 1280 * 1.2 || transform->position.y < 0 || transform->position.y > 960 * 1.2)
	{
		return true;
	}
	return false;
}
