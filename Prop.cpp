#include "Prop.h"

Prop::Prop(Vector2 position, std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger)
{
	tag = Tag::PROP;

	transform->SetPosition(position);
	
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->SetSortingOrder(1);
	spriteRenderer->SetSprite(AssetManager::GetSprite(spriteName));

	if (colliderType == ColliderType::BOX)
	{
		collider = AddComponent<BoxCollider>();
		BoxCollider* boxCollider = static_cast<BoxCollider*>(collider);
		boxCollider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));

	}
	else if (colliderType == ColliderType::CIRCLE)
	{
		collider = AddComponent<CircleCollider>();	
		CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
		circleCollider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));
	}

	if (collider != nullptr)
	{
		collider->isStatic = isStatic;
		collider->isTrigger = isTrigger;
	}
}

Prop::~Prop()
{
	
}

void Prop::Update(float deltaTime)
{
	//std::cout << "Position" << transform->position << endl;
	//std::cout << "collider" << collider->GetPosition() << endl;
	if (collider) collider->Update();
}

void Prop::Draw()
{
	spriteRenderer->Draw(transform->GetPosition());
}
