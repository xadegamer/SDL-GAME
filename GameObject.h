#pragma once

#include <iostream>

#include "Component.h"
#include "AssetManager.h"
#include "SpriteRenderer.h"
#include "Animator.h"

#include "Vector2.h"

class GameObject
{
protected:
	std::vector<Component*> components;
	Vector2 position;
	float angle;

	std::string textureID;
	Sprite* sprite;

	int currentFrame;
	int currentRow;

public:
	GameObject();
	~GameObject();

	void Update();
	void Render();
	
	void SetPosition(Vector2 position);
	Vector2* ModifyPosition();
	Vector2 GetPosition();

	void SetAngle(float angle);

public:
	bool CheckIfComponentExits(Component* newComponent);

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
};

