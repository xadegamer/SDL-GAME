#include "GasCylinder.h"

#include "AnimationControlledVfxEffect.h"

#include "HealthComponent.h"

GasCylinder::GasCylinder(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger) : Prop(position, spriteName, colliderType,sortingOrder, isStatic, isTrigger)
{
	tag = Tag::GAS_CYLINDER;

	detonateTime = 1;
	currentLifeTime = 0;
	explosionRadius = 200;
	damage = 100;
	hasTriggerExplosion = false;
	exploded = false;
}

GasCylinder::~GasCylinder()
{

}

void GasCylinder::Update(float deltaTime)
{
	Prop::Update(deltaTime);
	
	if (hasTriggerExplosion && !exploded)
	{
		currentLifeTime += deltaTime;
		if (currentLifeTime >= detonateTime)
		{
			Explosion();
		}
	}
}

void GasCylinder::TriggerExplosion()
{
	if (!hasTriggerExplosion && !exploded)
	{
		hasTriggerExplosion = true;
		smokeEffect = new AnimationControlledVfxEffect(collider->GetPosition(), "SmokeBeam", 2, SortingLayer::VfxLayer,false, false);
	}
}

void GasCylinder::Explosion()
{
	if (exploded) return;
	exploded = true;
	
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		if (GameObject::GetActiveGameobjects()[i] == nullptr || GameObject::GetActiveGameobjects()[i] == this) continue;
		if (GameObject::GetActiveGameobjects()[i]->CompareTag(Tag::ENEMY) || GameObject::GetActiveGameobjects()[i]->CompareTag(Tag::GAS_CYLINDER))
		{
			float distance = Vector2::Distance(GameObject::GetActiveGameobjects()[i]->GetTransform()->GetPosition(), transform->GetPosition());
			if (distance < explosionRadius)
			{
				HealthComponent* healthComponent = nullptr;
				if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<HealthComponent>(healthComponent)) healthComponent->TakeDamage(damage);
				else
				{
					GasCylinder* gasCylinder = dynamic_cast<GasCylinder*>(GameObject::GetActiveGameobjects()[i]);
					if (gasCylinder != nullptr && gasCylinder != this) gasCylinder->TriggerExplosion();
				}
			}
		}
	}

	Instantiate<AnimationControlledVfxEffect>(new AnimationControlledVfxEffect(collider->GetPosition(), "ExplosionEffect", 8, SortingLayer::VfxLayer,false));

//	Instantiate<VfxEffect>(new VfxEffect(collider->GetPosition(), "SmokeEffect", 8, false));

	std::string soundName = "Fire Explosion 0";
	soundName += std::to_string(MathUtility::RandomRange(1, 4));
	AudioManager::PlaySoundEffect(AssetManager::GetSoundEffect(soundName), false);

	GameObject::Destroy(this);
	if (smokeEffect)GameObject::Destroy(smokeEffect);
}
