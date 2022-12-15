#include "Health.h"

HealthComponent::HealthComponent()
{
}

HealthComponent::~HealthComponent()
{
	
}

void HealthComponent::TakeDamage(float damage)
{
	if (health == 0) return;
	
	health = MathUtility::Clamp(health - damage, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if (health <= 0)
	{
		if (OnDeathEvent)OnDeathEvent();
	}
	else { if (OnTakeDamageEvent)OnTakeDamageEvent(); }
}

void HealthComponent::Heal(float healAmount)
{
	health = MathUtility::Clamp(health + healAmount, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if (OnHealEvent) OnHealEvent();
}

void HealthComponent::SetHealth(float health)
{
	this->health = health;  maxHealth = health;
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
}
