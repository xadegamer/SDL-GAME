#include "HealthComponent.h"

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

bool HealthComponent::Heal(float healAmount)
{
	if (health == maxHealth) return false;
	health = MathUtility::Clamp(health + healAmount, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if (OnHealEvent) OnHealEvent();
	return true;
}

void HealthComponent::SetHealth(float health)
{
	this->health = health;  maxHealth = health;
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
}
