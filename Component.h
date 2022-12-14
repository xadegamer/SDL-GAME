#pragma once

#include <iostream>

class GameObject;

class Component
{
private:
	
	std::string name;
	
public:
	GameObject* gameObject;
	virtual void someFunc();
};

