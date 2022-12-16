#include "TimedDelayVfxEffect.h"

TimedDelayVfxEffect::TimedDelayVfxEffect(Vector2 position, std::string spriteID, int sortingOrder, float duration) : GameObject(position)
{
	this->duration = duration;
	this->spriteRenderer = AddComponent <SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSprite(AssetManager::GetSprite(spriteID));
	spriteRenderer->SetSortingOrder(sortingOrder);

	Vector2 center = Vector2(spriteRenderer->GetSprite()->textureWidth / 2, spriteRenderer->GetSprite()->textureHeight / 2);
	transform->SetPosition(transform->GetPosition() - center);
}

TimedDelayVfxEffect::~TimedDelayVfxEffect()
{
}

void TimedDelayVfxEffect::Update(float deltaTime)
{
	currentLifeTime += deltaTime;
	if (currentLifeTime >= duration)
	{
		isDestroyed = true;
		GameObject::Destroy(this);
	}

	GameObject::Update(deltaTime);
}

void TimedDelayVfxEffect::Draw()
{
	spriteRenderer->Draw(transform->GetPosition());
}
