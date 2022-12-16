#include "Canvas.h"

Canvas::Canvas(std::string id, Vector2 size, Vector2 position, bool hasBackground)
{
	activeDelay = 0.1f;
	activeTimer = 0;
	
	ID = id;
	this->hasBackground = hasBackground;
	rect = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };

	//random 1 - 2 backround image
	int randomNum = rand() % 2;
	backgroundSprite = AssetManager::GetSprite(randomNum == 1 ? "background" : "background2");
}

Canvas::~Canvas()
{
	for (auto& uiObjects : uiObjects)
	{
		delete uiObjects;
		uiObjects = nullptr;
	}
	uiObjects.clear();
	backgroundSprite = nullptr;
}

void Canvas::Show()
{
	isEnable = true;
}

void Canvas::Hide()
{
	isActive = false;
	isEnable = false;
}

void Canvas::AddUIObject(UIObject* uiObject)
{
	uiObjects.push_back(uiObject);
}

void Canvas::Draw()
{
	if (isEnable)
	{
		if (hasBackground)
		{
			// render background sprite
			if (backgroundSprite != nullptr) SDL_RenderCopy(SDLManager::GetRenderer(), backgroundSprite->texture, NULL, &rect);
			else
			{
				SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 0, 0);
				SDL_RenderFillRect(SDLManager::GetRenderer(), &rect);
			}
		}	
		for (auto& uiObject : uiObjects) uiObject->Draw();
	}
}

void Canvas::Update(float deltaTime)
{
	if (isEnable && !isActive)
	{
		if (activeTimer >= activeDelay)
		{
			isActive = true;
			activeTimer = 0;
		}
		else activeTimer += deltaTime;
	}
	
	if (isActive && isEnable) for (auto& uiObject : uiObjects) uiObject->Update();
}

UIObject* Canvas::GetUIObjectByID(std::string id)
{
	for (auto& uiObject : uiObjects)
	{
		if (uiObject->GetID() == id) return uiObject;
	}
	return nullptr;
}
