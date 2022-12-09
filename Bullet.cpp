#include "Bullet.h"

Bullet::Bullet(Vector2 startPosition, BulletType type, Vector2 direction)
{	
	tag = Tag::BULLET;
	
	transfrom->position = startPosition;

	bulletType = type;
	
	spriteRenderer = AddComponent<SpriteRenderer>();

	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	animator->AddAnimationClip("Idle", AssetManager::GetSprite("Bullet"), 3, 0.05);

	rigidBody = AddComponent<RigidBody>();
	rigidBody->gravity = 0;
	if (bulletType == BulletType::PLAYER) direction = GetDirectionToMouse(transfrom->position);
	rigidBody->ApplyForce(direction * moveSpeed);

	collider = AddComponent<Collider>();
	collider->SetUp(Circle, transfrom, Vector2(animator->GetCurrentAnimationClip()->animPixelWidth, animator->GetCurrentAnimationClip()->animPixelHeight), Vector2(7,10));

	//transfrom->rotation = GetAngleFromMouse(transfrom->position, animator->GetCurrentAnimationClip()->animPixelHeight, animator->GetCurrentAnimationClip()->animPixelWidth);

	collider->AssignCollisonCallBack([](Collider* other)
	{
		if (other->gameObject->CompareTag(Tag::ENEMY))
		{
			std::cout << "Bullet Hit Enemy" << std::endl;
		}
	});

}

Bullet::~Bullet()
{
	
}

void Bullet::Update(float deltaTime)
{
	transfrom->Translate(rigidBody->GetPosition());
	animator->Update(deltaTime);
	collider->Update();

	//std::cout << "Bullet: " << transfrom->position.x << ", " << transfrom->position.y << std::endl;
	//std::cout << "Bullet: " << rigidBody->GetPosition().x << ", " << rigidBody->GetPosition().y << std::endl;

	rigidBody->Update(deltaTime);
}

void Bullet::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transfrom->position, transfrom->rotation, animator->GetRect());
}
