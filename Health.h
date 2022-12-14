#pragma once

#include "Component.h"
#include <string>
#include <functional>
#include <map>
#include "SDL.h"
#include "Vector2.h"
#include "MathUtility.h"

class Health : public Component
{	
private:
	
	float health;
	float maxHealth;

public:

	std::function <void(float normalisedHealth)> OnHealthChangeEvent;
	std::function <void()> OnTakeDamageEvent;
	std::function <void()> OnHealEvent;
	std::function <void()> OnDeathEvent;
	
	Health();
	~Health();

	void TakeDamage(float damage);
	void Heal(float healAmount);

	void SetHealth(float health);
	inline float GetHealth() { return health; }
	inline int GetMaxHealth() { return maxHealth; }
	inline bool GetIsDead() { return health <= 0; }
};

