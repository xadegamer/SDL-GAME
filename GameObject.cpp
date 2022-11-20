#include "GameObject.h"

GameObject::GameObject()
{
	//AddComponent<SpriteRenderer>()->Load("Assets/Character.png", "Player", m_pRenderer);
}

GameObject::~GameObject()
{
}

void GameObject::Load(int x, int y, std::string textureID)
{
	position.x = x;
	position.y = y;

	this->textureID = textureID;

	currentRow = 1;
	currentFrame = 1;
}

void GameObject::Update()
{
}

void GameObject::Render(SDL_Renderer* pRenderer)
{

	SpriteRenderer* renderer = GetComponent<SpriteRenderer>();
	renderer->name = "SpriteRenderer";
	//std::cout << renderer->name << std::endl;
	
	//if (renderer != nullptr) renderer->DrawFrame(textureID, position.x, position.y, width, height, currentRow, currentFrame, pRenderer);

	//if (renderer != nullptr) renderer->Draw(textureID, position.x, position.y, 6 , 2, pRenderer);

	if (renderer != nullptr) renderer->Animate(textureID, position,6, 2, currentRow, currentFrame, angle, pRenderer);
}

void GameObject::SetPosition(Vector2 position)
{
	this->position = position;
}

Vector2* GameObject::ModifyPosition()
{
	return &position;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetAngle(float angle)
{
	this->angle = angle;
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

