#pragma once

#include <iostream>

class GameObject;

class Component
{
	
public:
	std::string name;
	GameObject* gameObject;
	virtual void someFunc();
};

