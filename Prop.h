#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

enum class ColliderType {None,BOX,CIRCLE};

class Prop : public GameObject
{
protected:
	ColliderType colliderType;
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Collider* collider;
	
public:
	Prop(std::string spriteName, ColliderType colliderType, bool isStatic, bool isTrigger);
	~Prop();

	void Update(float deltaTime) override;
	void Draw() override;
};

