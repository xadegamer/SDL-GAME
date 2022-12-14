#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	float radius;
	void SetUp(Transform* owner, Vector2 size, float radiousMutiplier = 1, Vector2 offset = Vector2(0, 0), bool isStatic = false);
	void Draw() override;
};

