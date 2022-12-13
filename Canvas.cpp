#include "Canvas.h"

Canvas::Canvas(std::string id, Vector2 size, Vector2 position, bool hasBackground)
{
	ID = id;
	this->hasBackground = hasBackground;
	background = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };
	backgroundSprite = AssetManager::GetSprite("background");
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
	isActive = true;
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
	if (isActive)
	{
		if (hasBackground)
		{
			// render background sprite
			if (backgroundSprite != nullptr) SDL_RenderCopy(SDLManager::GetRenderer(), backgroundSprite->texture, NULL, &background);
			else
			{
				SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 0, 0);
				SDL_RenderFillRect(SDLManager::GetRenderer(), &background);
			}
		}	
		for (auto& uiObject : uiObjects) uiObject->Draw();
	}
}

void Canvas::Update()
{
	if (isActive && isEnable) for (auto& uiObject : uiObjects) uiObject->Update();
}
