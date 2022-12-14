#include "Health.h"

Health::Health()
{
}

Health::~Health()
{
	
}

void Health::TakeDamage(float damage)
{
	health = Clamp(health - damage, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
	if(health <= 0) OnDeathEvent();
}

void Health::Heal(float healAmount)
{
	health = Clamp(health + healAmount, 0, maxHealth);
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
}

void Health::SetHealth(float health)
{
	this->health = health;  maxHealth = health;
	if(OnHealthChangeEvent) OnHealthChangeEvent(health / maxHealth);
}
