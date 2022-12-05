#pragma once 

#include "Component.h"
#include "Vector2.h"

#include <iostream>

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	// Setters for gravity and mass
	inline void SetMass(float mass) { this->mass = mass; }
	inline void SetGravity(float gravity) { this->gravity = gravity; }

	// Force
	inline void ApplyForce(Vector2 force) { this->force = force; }
	inline void ApplyForceX(float x) {this->force.x = x;}
	inline void ApplyForceY(float y) {this->force.y = y;}
	inline void ResetForce() { this->force = Vector2(0, 0); }

	//Friction
	inline void ApplyFriction(Vector2 friction) { this->friction = friction; }
	inline void ResetFriction() { this->friction = Vector2(0, 0); }

	// Velocity
	inline void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	inline void SetVelocityX(float x) { this->velocity.x = x; }
	inline void SetVelocityY(float y) { this->velocity.y = y; }

	// Getters
	inline float GetMass() { return  mass; }
	inline Vector2 GetPosition() { return position; }
	inline Vector2 GetVelocity() { return velocity; }
	inline Vector2 GetAcceleration() { return acceleration; }

	// Gravity
	
	
	// Update
	void Update(float deltaTime);

public:
	
	float gravity;

	Vector2 position;
	Vector2 velocity;

private:	
		
	float mass;
	
	Vector2 force;	
	Vector2 friction;
	
	Vector2 acceleration;
};

