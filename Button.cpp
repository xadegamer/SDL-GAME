#include "Button.h"


Button::Button(std::string id, Vector2 position, Vector2 startSize, int padding)
{
	this->ID = id;
	layer = 0;
	anchorPositon = position;
	size = startSize;
	this->padding = padding;

	size.x += padding;
	size.y += padding;

	centerPositon = anchorPositon - (size / 2);
	rect = { (int)centerPositon.x, (int)centerPositon.y, (int)size.x , (int)size.y};
	currentState = buttonState::DEFAULT;
}

Button::~Button()
{
	if (text != nullptr) delete text;
}

void Button::Draw()
{
    switch (currentState)
    {
    case buttonState::DEFAULT:
        SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255, 255, 255, 255);
        SDL_RenderDrawRect(SDLManager::GetRenderer(), &rect);
        break;
    case buttonState::HOVERED:
        SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 100, 100, 100, 100);
        SDL_RenderFillRect(SDLManager::GetRenderer(), &rect);
        SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 200, 200, 200, 255);
        SDL_RenderDrawRect(SDLManager::GetRenderer(), &rect);
        break;
    case buttonState::PRESSED:
        SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 50, 50, 50, 100);
        SDL_RenderFillRect(SDLManager::GetRenderer(), &rect);
        SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 150, 150, 150, 255);
        SDL_RenderDrawRect(SDLManager::GetRenderer(), &rect);
        break;
    }
	
	if (text != nullptr) text->Draw();
}

void Button::Update()
{	
	// check if mouse is inside button
	if (IsPointInRect(InputManager::GetMousePosition(), centerPositon, size))
	{
		if (InputManager::GetMouseButtonDown(InputManager::LEFT))
		{
			if (OnClick) OnClick();
			currentState = buttonState::PRESSED;
		}
		else
		{
			if (currentState != buttonState::HOVERED)
			{
				if (OnMouseOver) OnMouseOver();
				
				currentState = buttonState::HOVERED;
			}
		}
	}
	else
	{
		currentState = buttonState::DEFAULT;
	}

	if (text != nullptr) text->Update();
}

void Button::AddText(std::string id,std::string inputText, std::string fontID, SDL_Color color)
{
	text = new Text(id, inputText, fontID, color, anchorPositon);

	text->OnTextChange = [this]()
	{
		if (text->size.x > size.x)
		{
			std::cout << "Button is too small to fit text" << std::endl;
		}
	};
	
	rect = { (int)centerPositon.x, (int)centerPositon.y, (int)size.x , (int)size.y };
}

void Button::SetText(std::string inputText)
{
	text->SetText(inputText);
}