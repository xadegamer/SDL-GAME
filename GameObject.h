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
	Gas_Cylinder
};

class GameObject
{
protected:

	static std::vector<GameObject*> activeGameobjects;

	std::vector<Component*> components;
	Tag tag = Tag::DEFAULT;
	Transform* transform;
	bool isDestroyed = false;

public:
	GameObject(Vector2 position = Vector2(0, 0));
	virtual ~GameObject();
	
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw() {};

	inline Transform* GetTransform() { return transform; }
	inline Tag GetTag() { return tag; }
	inline void SetTag(Tag tag) { this->tag = tag; }

public:

	template<class T>
	T* AddComponent(T* newCom)
	{
		Component* newComponent = dynamic_cast<Component*>(newCom);

		if (CheckIfComponentExits(newComponent)) std::cout << "Already Exists" << std::endl;
		newComponent->SetGameObject(this);
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

	template<class T>
	static T* InstantiateRandomPositionInLevel(T* prefab)
	{
		Vector2 randomPosition = Vector2(MathUtility::RandomRange(0, 2560), MathUtility::RandomRange(0, 1920));
		//while (GameObjectInRange(randomPosition, 5)) randomPosition = Vector2(MathUtility::RandomRange(0, 2560), MathUtility::RandomRange(0, 1920));
		return Instantiate(prefab, randomPosition);
	}

	template<class T>
	static T* InstantiateRandomPositionOnScreen(T* prefab)
	{
		SDL_Rect cameraRect = Camera::GetViewBox();
		Vector2 randomPosition = Vector2(MathUtility::RandomRange(cameraRect.x, cameraRect.x + cameraRect.w), MathUtility::RandomRange(cameraRect.y, cameraRect.y + cameraRect.h));

		//while (GameObjectInRange(randomPosition, 5)) randomPosition = Vector2(MathUtility::RandomRange(cameraRect.x, cameraRect.x + cameraRect.w), MathUtility::RandomRange(cameraRect.y, cameraRect.y + cameraRect.h));

		return Instantiate(prefab, randomPosition);
	}

	template<class T>
	static T* Instantiate(T* prefab)
	{
		T* newObject = new T(*prefab);
		return newObject;
	}

	bool CompareTag( Tag tag)
	{
		if (this->tag == tag) return true;
		else return false;
	}

	void CheckComponent(Component* newCom);

	bool CheckIfComponentExits(Component* newComponent);

	static bool GameObjectInRange(Vector2 position, float range);

	virtual void OnCollisionEnter(Collider* other) {};
	
	inline static std::vector<GameObject*> GetActiveGameobjects() { return activeGameobjects; }
	
	inline bool IsDestroyed() { return isDestroyed;}

	static void Destroy(GameObject* gameObject);

	static void DestroyAllGameObjects();	

	static GameObject* FindGameObjectWithTag(Tag tag);
};