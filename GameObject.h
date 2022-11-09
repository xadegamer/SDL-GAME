#pragma once
#include "Component.h"

class GameObject
{
public:

	std::vector<Component*> components;

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

	void CheckComponent(Component* newCom);
};

