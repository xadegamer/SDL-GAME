#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radious;

public:
	void SetUp(Transform* owner, Vector2 size, Vector2 offset = Vector2(0, 0), bool isStatic = false) override;

	void Draw() override;
};

