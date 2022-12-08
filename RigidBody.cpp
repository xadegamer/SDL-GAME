#include "Rigidbody.h"

#define GRAVITY 9.8f

RigidBody::RigidBody()
{
	gravity = GRAVITY;
	mass = 1.0f;
}

RigidBody::~RigidBody()
{
	
}

void RigidBody::Update(float deltaTime)
{
	// Calculate acceleration
	acceleration.x = (force.x + friction.x) / mass;
	
	acceleration.y = gravity + (force.y / mass);

	// Calculate velocity
	
	velocity = acceleration * deltaTime;

	// Calculate position
	
	position = velocity;
}
