#include "Character.h"

Character::Character()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	animator = AddComponent<Animator>();
	animator->SetSprite(spriteRenderer->GetSprite());
	rigidBody = AddComponent<RigidBody>();
	rigidBody->gravity = 0;
}

Character::~Character()
{
}

void Character::Update(float deltaTime)
{
	
}

void Character::Draw()
{
	spriteRenderer->Draw(animator->GetSprite()->texture, transform->position, transform->rotation, animator->GetRect());
}
