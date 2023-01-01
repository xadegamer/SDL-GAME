#include "AnimationControlledVfxEffect.h"

AnimationControlledVfxEffect::AnimationControlledVfxEffect(Vector2 position, std::string spriteID,int numberOfFrame, int sortingOrder, bool applyOffset, bool destroyOnLastFrame) : GameObject(position)
{
	this->spriteRenderer = AddComponent <SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(sortingOrder);
	
	this->animator = AddComponent < Animator>(new Animator);
	animator->SetSprite(spriteRenderer->GetSprite());
	
	if (destroyOnLastFrame)
	{
		this->animator->AddAnimationClip("Effect", AssetManager::GetSprite(spriteID), numberOfFrame, 0.05, false)->AddAnimationEvent("End Event", numberOfFrame - 1, [=]() {OnAnimationEnd(); });
	}
	else this->animator->AddAnimationClip("Effect", AssetManager::GetSprite(spriteID), numberOfFrame, 0.05, false);

	
	if (applyOffset)
	{
		Vector2 center = Vector2(animator->GetCurrentAnimationClip()->animPixelWidth / 2, animator->GetCurrentAnimationClip()->animPixelHeight / 2);
		transform->SetPosition(transform->GetPosition() - center);
	}
}

AnimationControlledVfxEffect::~AnimationControlledVfxEffect()
{
	
}

void AnimationControlledVfxEffect::Update(float deltaTime)
{
	animator->Update(deltaTime);
	GameObject::Update(deltaTime);
}

void AnimationControlledVfxEffect::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->GetPosition(), transform->GetRotation(), animator->GetRect());
}

void AnimationControlledVfxEffect::OnAnimationEnd()
{
	GameObject::Destroy(this);
}
