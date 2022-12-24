#pragma once

#include "Component.h"
#include <string>
#include <functional>
#include <map>
#include "SDL.h"
#include "Vector2.h"
#include "MathUtility.h"

class HealthComponent : public Component
{	
private:
	
	float health;
	float maxHealth;
	
	std::function <void(float normalisedHealth)> OnHealthChangeEvent;
	std::function <void()> OnTakeDamageEvent;
	std::function <void()> OnHealEvent;
	std::function <void()> OnDeathEvent;

public:

	HealthComponent();
	~HealthComponent();	

	inline std::function <void(float normalisedHealth)>& GetOnHealthChangeEvent() { return OnHealthChangeEvent; }
	inline std::function <void()>& GetOnTakeDamageEvent() { return OnTakeDamageEvent; }
	inline std::function <void()>& GetOnHealEvent() { return OnHealEvent; }
	inline std::function <void()>& GetOnDeathEvent() { return OnDeathEvent; }

	void TakeDamage(float damage);
	bool Heal(float healAmount);

	void SetHealth(float health);
	inline float GetHealth() { return health; }
	inline int GetMaxHealth() { return maxHealth; }
	inline bool GetIsDead() { return health <= 0; }
};

