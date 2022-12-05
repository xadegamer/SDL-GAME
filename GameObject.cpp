#include "GameObject.h"

GameObject::GameObject()
{
	transfrom = AddComponent<Transform>();
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

	if (renderer != nullptr) renderer->Draw(aimator->GetSprite()->texture, transfrom->position, 3, transfrom->rotation, aimator->GetRect());
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

