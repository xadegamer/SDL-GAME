#include "Canvas.h"

std::vector<Canvas*> Canvas::activeCanvases;

Canvas::Canvas(std::string id, Vector2 size, Vector2 position)
{
	ID = id;
	background = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };
	activeCanvases.push_back(this);
}

Canvas::~Canvas()
{
	for (auto& uiObjects : uiObjects)
	{
		delete uiObjects;
		uiObjects = nullptr;
	}

	uiObjects.clear();
}

void Canvas::Show()
{
	isActive = true;
}

void Canvas::Hide()
{
	isActive = false;
}

void Canvas::AddUIObject(UIObject* uiObject)
{
	uiObjects.push_back(uiObject);
}

void Canvas::Draw()
{
	if (isActive)
	{
		SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 50, 50, 50, 100);
		SDL_RenderFillRect(SDLManager::GetRenderer(), &background);
		for (auto& uiObject : uiObjects) uiObject->Draw();
	}
}

void Canvas::Update()
{
	if (isActive) for (auto& uiObject : uiObjects) uiObject->Update();
}

void Canvas::EnableCanvasByID(std::string id)
{
	for (auto& canvas : activeCanvases)
	{
		if (canvas->ID == id) canvas->Show(); else canvas->Hide();
	}
}