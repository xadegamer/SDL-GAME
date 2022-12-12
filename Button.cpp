#include "Button.h"


Button::Button(Vector2 position, Vector2 startSize, int padding)
{
	layer = 0;
	transform->position = position;
	size = startSize;
	this->padding = padding;

	size.x += padding;
	size.y += padding;

	rect = { (int)transform->position.x, (int)transform->position.y, (int)size.x , (int)size.y};
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
	if (IsPointInRect(InputManager::GetMousePosition(), transform->position, size))
	{
		if (InputManager::GetMouseButtonDown(InputManager::LEFT))
		{
			if (OnClick != nullptr) OnClick();
			currentState = buttonState::PRESSED;
		}
		else
		{
			currentState = buttonState::HOVERED;
		}
	}
	else
	{
		currentState = buttonState::DEFAULT;
	}

	if (text != nullptr) text->Update();
}

void Button::AddText(std::string inputText, std::string fontID, SDL_Color color)
{
	Vector2 centerOfButton = transform->position + (size / 2);
	
	text = new Text(inputText, fontID, color, centerOfButton);

	text->OnTextChange = [this]()
	{
		// scale button to fit text
		if (text->size.x > size.x)
		{
			std::cout << "Button is too small to fit text" << std::endl;
			size = text->size;
			size.x += padding;
			size.y += padding;
			rect = { (int)transform->position.x, (int)transform->position.y, (int)size.x,(int)size.y };
		}
	};
	
	rect = { (int)transform->position.x, (int)transform->position.y, (int)size.x,(int)size.y };
}

void Button::SetText(std::string inputText)
{
	text->SetText(inputText);
}