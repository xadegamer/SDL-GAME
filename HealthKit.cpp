#include "HealthKit.h"

#include "Player.h"

HealthKit::HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder) : Prop(position, spriteName, colliderType, sortingOrder, true, true)
{
	healAmount = 50;
	tag = Tag::DEFAULT;
	collider->OnCollisionEnterEvent = std::bind(&HealthKit::OnCollisionEnter, this, std::placeholders::_1);
}

HealthKit::~HealthKit()
{
	
}
void HealthKit::OnCollisionEnter(Collider* other)
{
	Player* player = dynamic_cast<Player*>(other->GetGameObject());
	if (player)
	{
		if (player->GetComponent<HealthComponent>()->Heal(healAmount))
		{
			PickUp();
		}
	}
}

void HealthKit::PickUp()
{
	isDestroyed = true;
	Destroy(this);
}