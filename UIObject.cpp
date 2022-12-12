#include "UIObject.h"

std::vector<UIObject*> UIObject::activeUIObjects;

UIObject::UIObject()
{
	transform = new Transform();
	activeUIObjects.push_back(this);
}

UIObject::~UIObject()
{
	transform = nullptr;
	SDL_DestroyTexture(texture);	
}

void UIObject::Draw()
{
	
}

void UIObject::Update()
{
	
}

void UIObject::Destroy(UIObject* uiObject)
{
	activeUIObjects.erase(find(activeUIObjects.begin(), activeUIObjects.end(), uiObject));
	delete uiObject;
	uiObject = nullptr;
}

void UIObject::DestroyAll()
{
	for (auto& uiObject : activeUIObjects)
	{
		delete uiObject;
		uiObject = nullptr;
	}
	activeUIObjects.clear();
}