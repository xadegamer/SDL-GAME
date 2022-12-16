#include "GasCylinder.h"

#include "VfxEffect.h"

#include "HealthComponent.h"

GasCylinder::GasCylinder(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger) : Prop(position, spriteName, colliderType,sortingOrder, isStatic, isTrigger)
{
	tag = Tag::Gas_Cylinder;
}

GasCylinder::~GasCylinder()
{
	
}

void GasCylinder::Update(float deltaTime)
{
	Prop::Update(deltaTime);
	
	if (hasTriggerExplosion)
	{
		currentLifeTime += deltaTime;
		if (currentLifeTime >= detonateTime) Explosion();
	}
}

void GasCylinder::TriggerExplosion()
{
	if (!hasTriggerExplosion && !isDestroyed)
	{
		hasTriggerExplosion = true;
		Instantiate<VfxEffect>(new VfxEffect(collider->GetPosition(),"SmokeEffect", 8));
	}
}

void GasCylinder::Explosion()
{
	std::cout << "Gas Cylinder hit by bullet" << std::endl;
	
	isDestroyed = true;

	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		if (GameObject::GetActiveGameobjects()[i]->CompareTag(Tag::ENEMY) || GameObject::GetActiveGameobjects()[i]->CompareTag(Tag::Gas_Cylinder))
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
	
	Instantiate<VfxEffect>(new VfxEffect(collider->GetPosition(),"SmokeEffect", 8));
	Instantiate<VfxEffect>(new VfxEffect(collider->GetPosition(),"ExplosionEffect", 8));
	Destroy(this);
}
