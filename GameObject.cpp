#include "GameObject.h"

//define the static variable
std::vector<GameObject*> GameObject::activeGameobjects = std::vector<GameObject*>();

GameObject::GameObject(Vector2 position)
{
	activeGameobjects.push_back(this);
	transform = AddComponent<Transform>(new Transform);
	transform->SetPosition(position);
}

GameObject::~GameObject()
{
	for (auto& component : components)
	{
		delete component;
		component = nullptr;
	}
}

bool GameObject::CheckIfComponentExits(Component* newComponent)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (typeid(*newComponent).name() == typeid(*components[i]).name()) return true;
	}
	return false;
}

bool GameObject::GameObjectInRange(Vector2 position, float range)
{
	for (size_t i = 0; i < activeGameobjects.size(); i++)
	{
		float distance = Vector2::Distance(activeGameobjects[i]->GetTransform()->GetPosition(), position);
		if (distance < range) return true;
	}
	return false;
}

void GameObject::Destroy(GameObject* gameObject)
{
	activeGameobjects.erase(find(activeGameobjects.begin(), activeGameobjects.end(), gameObject));
	delete gameObject;
	gameObject = nullptr;
}

void GameObject::DestroyAllGameObjects()
{
	for (auto& gameObject : activeGameobjects)
	{
		delete gameObject;
		gameObject = nullptr;
	}
	activeGameobjects.clear();
}

GameObject* GameObject::FindGameObjectWithTag(Tag tag)
{
	for (auto& gameObject : activeGameobjects)
	{
		if (gameObject->tag == tag) return gameObject;
	}
	return nullptr;
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

