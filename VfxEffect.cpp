#include "VfxEffect.h"

VfxEffect::VfxEffect(Vector2 position, std::string spriteID,int numberOfFrame) : GameObject(position)
{
	this->spriteRenderer = AddComponent <SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(2);
	
	this->animator = AddComponent < Animator>(new Animator);
	animator->SetSprite(spriteRenderer->GetSprite());
	this->animator->AddAnimationClip("Effect", AssetManager::GetSprite(spriteID), numberOfFrame, 0.05, false)->AddAnimationEvent("End Event", numberOfFrame - 1, [=]() {OnAnimationEnd(); });

	//get center of sprite
	Vector2 center = Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2);
	// set position to center of sprite
	transform->SetPosition(transform->GetPosition() - center);
}

VfxEffect::~VfxEffect()
{
	
}

void VfxEffect::Update(float deltaTime)
{
	if (!isDestroyed)
	{
		this->animator->Update(deltaTime);
	}
	else
	{
		currentLifeTime += deltaTime;
		if (currentLifeTime >= clearTime)
		{
			GameObject::Destroy(this);
		}
	}
}

void VfxEffect::Draw()
{
	if (!isDestroyed) spriteRenderer->Draw(animator->GetSprite()->texture, transform->GetPosition(), transform->GetRotation(), animator->GetRect());
}

void VfxEffect::OnAnimationEnd()
{
	isDestroyed = true;
}
