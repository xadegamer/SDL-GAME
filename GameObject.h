#pragma once

#include <iostream>

#include "Component.h"

#include "SpriteRenderer.h"
#include "Animator.h"
#include "Transform.h"
#include "RigidBody.h"

#include "AssetManager.h"
#include"AudioManager.h"

#include "Vector2.h"
#include "MathUtility.h"

#include "Camera.h"

class Collider;

enum Tag
{
	DEFAULT,
	PLAYER,
	ENEMY,
	BULLET,
};

class GameObject
{
protected:

	static std::vector<GameObject*> activeGameobjects;

	std::vector<Component*> components;

public:
	GameObject();
	virtual ~GameObject();
	
	Tag tag = Tag::DEFAULT;

	Transform* transform;

	virtual void Update(float deltaTime) {};
	virtual void Draw() {};

public:

	template<class T>
	T* AddComponent()
	{
		T* newCom = new T;

		Component* newComponent = dynamic_cast<Component*>(newCom);

		if (CheckIfComponentExits(newComponent)) std::cout << "Already Exists" << std::endl;
		newComponent->gameObject = this;
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
	bool TryGetComponent(T*& component)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return true;
		}
		return false;
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

	bool CompareTag( Tag tag)
	{
		if (this->tag == tag) return true;
		else return false;
	}

	void CheckComponent(Component* newCom);

	bool CheckIfComponentExits(Component* newComponent);

	virtual void OnCollisionEnter(Collider* other) {};

	virtual void OnTriggerEnter(Collider* other) {};
	
	inline static std::vector<GameObject*> GetActiveGameobjects() { return activeGameobjects; }

	static void Destroy(GameObject* gameObject);

	static void DestroyAllGameObjects();	
};

