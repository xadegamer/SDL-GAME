#include "Health.h"

Health::Health()
{
}

Health::~Health()
{
	
}

void Health::TakeDamage(float damage)
{
	if (health == 0) return;
	
	health = Clamp(health - damage, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if (health <= 0)
	{
		if (OnDeathEvent)OnDeathEvent();
	}
	else { if (OnTakeDamageEvent)OnTakeDamageEvent(); }
}

void Health::Heal(float healAmount)
{
	health = Clamp(health + healAmount, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if (OnHealEvent) OnHealEvent();
}

void Health::SetHealth(float health)
{
	this->health = health;  maxHealth = health;
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
}
