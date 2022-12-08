#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Translate(Vector2 translation)
{
	position += translation;
}

void Transform::TranslateX(float x)
{
	position.x += x;
}

void Transform::TranslateY(float y)
{
	position.y += y;
}

void Transform::Log()
{
	std::cout << "Position: " << position << std::endl;
	std::cout << "Scale: " << scale << std::endl;
	std::cout << "Rotation: " << rotation << std::endl;
}