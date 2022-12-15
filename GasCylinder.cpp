#include "GasCylinder.h"

#include "VfxEffect.h"

#include "Health.h"

GasCylinder::GasCylinder(std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger) : Prop(spriteName, colliderType, isStatic, isTrigger)
{
	//collider->OnCollisionEnterEvent = std::bind(&GasCylinder::OnCollisionEnter, this, std::placeholders::_1);
	collider->OnCollisionEnterEvent = [=](Collider* other) {OnCollisionEnter(other); };
	tag = Tag::Gas_Cylinder;
}

GasCylinder::~GasCylinder()
{
	
}

void GasCylinder::Explosion()
{
	std::cout << "Gas Cylinder hit by bullet" << std::endl;
	
	for (int i = 0; i < GameObject::GetActiveGameobjects().size(); i++)
	{
		if (GameObject::GetActiveGameobjects()[i]->CompareTag(Tag::ENEMY))
		{
			float distance = Vector2::Distance(GameObject::GetActiveGameobjects()[i]->GetTransform()->GetPosition(), transform->GetPosition());
			if (distance < explosionRadius)
			{
				HealthComponent* healthComponent = nullptr;
				if (GameObject::GetActiveGameobjects()[i]->TryGetComponent<HealthComponent>(healthComponent)) healthComponent->TakeDamage(damage);
			}
		}
	}
	
	Instantiate<VfxEffect>(new VfxEffect("ExplosionEffect", 8), transform->GetPosition());
	Destroy(this);
}
