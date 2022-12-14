#include "Prop.h"

Prop::Prop(Vector2 position, std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger)
{
	tag = Tag::PROP;
	transform->position = position;
	
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(AssetManager::GetSprite(spriteName));

	spriteRenderer->GetSprite()->textureHeight /= 2;
	spriteRenderer->GetSprite()->textureWidth /= 2;

	if (colliderType == ColliderType::BOX)
	{
		collider = AddComponent<BoxCollider>();
		collider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));

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
	spriteRenderer->Draw(transform->position);
}
