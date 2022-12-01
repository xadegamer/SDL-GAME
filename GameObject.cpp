#include "GameObject.h"

GameObject::GameObject()
{
	//AddComponent<SpriteRenderer>()->Load("Assets/Character.png", "Player", m_pRenderer);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Render()
{
	SpriteRenderer* renderer = GetComponent<SpriteRenderer>();
	renderer->name = "SpriteRenderer";

	Animator* aimator = GetComponent<Animator>();

	if (aimator != nullptr) aimator->Animate();

	if (renderer != nullptr) renderer->Draw(aimator->GetSprite()->texture, position, 3, angle, aimator->GetRect());
}

void GameObject::SetPosition(Vector2 position)
{
	this->position = position;
}

Vector2* GameObject::ModifyPosition()
{
	return &position;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetAngle(float angle)
{
	this->angle = angle;
}

bool GameObject::CheckIfComponentExits(Component* newComponent)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (typeid(*newComponent).name() == typeid(*components[i]).name()) return true;
	}
	return false;
}

void GameObject::CheckComponent(Component* newCom)
{
	if (std::find(components.begin(), components.end(), newCom) != components.end())
	{
		std::cout << "Contains" << std::endl;
	}
	else
	{
		std::cout << "Not Contains" << std::endl;
	}
}

