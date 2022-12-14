#pragma once

#include <iostream>

class GameObject;

class Component
{
private:
	
	std::string name;
	GameObject* gameObject;
public:
	inline GameObject* GetGameObject() { return gameObject; }
	inline void SetGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
	virtual void someFunc();
};

