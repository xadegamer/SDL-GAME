#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radius;
	
public:

	void SetUp(Transform* owner, Vector2 size, float radiousMutiplier = 1, Vector2 offset = Vector2(0, 0), bool isStatic = false);
	void Draw() override;

	inline float GetRadius() { return radius; }
};

