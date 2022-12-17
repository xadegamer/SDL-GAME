#pragma once

#include "UIObject.h"
#include "Text.h"

enum class buttonState { DEFAULT, HOVERED, PRESSED };

class Button : public UIObject
{
	
protected:
	
	buttonState currentState;
	Text* text;
	
public:
	
	Button(std::string id, Vector2 position, Vector2 size);
	~Button() override;

	void Draw() override;
	void Update(float deltaTime) override;
	
	std::function <void()> OnClick;
	std::function <void()> OnMouseOver;

	void AddText(std::string id,std::string text, std::string fontID, SDL_Color color);
	
	void SetText(std::string text);
};

