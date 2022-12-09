#pragma once

#include <iostream>

#include "Component.h"

#include "SpriteRenderer.h"
#include "Animator.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"

#include "AssetManager.h"
#include"AudioManager.h"

#include "Vector2.h"
#include "MathUtility.h"

class GameObject
{
protected:

	std::vector<Component*> components;

public:
	GameObject();
	~GameObject();

	Transform* transfrom;

	virtual void Update(float deltaTime);
	virtual void Draw();

public:

	template<class T>
	T* AddComponent()
	{
		T* newCom = new T;

		Component* newComponent = dynamic_cast<Component*>(newCom);

		if (CheckIfComponentExits(newComponent)) std::cout << "Already Exists" << std::endl;
		else std::cout << "Dont Already Exists" << std::endl;

		components.push_back(newComponent);
		return newCom;
	}

	template<class T>
	T* GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return  component;
		}
	}

	template<class T>
	T* RemoveComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr)
			{
				components.erase(components.begin() + i);
				return component;
			}
		}
	}

	void CheckComponent(Component* newCom);

	bool CheckIfComponentExits(Component* newComponent);
};

