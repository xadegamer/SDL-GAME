#pragma once

#include "UIObject.h"
#include "Text.h"

enum class buttonState { DEFAULT, HOVERED, PRESSED };

class Button : public UIObject
{
	
protected:
	
	buttonState currentState;

	
public:
	
	Button(Vector2 position, Vector2 size, int padding = 0);
	~Button() override;

	void Draw() override;
	void Update() override;
	
	Text* text;
	int padding;
	std::function <void()> OnClick;

	void AddText(std::string text, std::string fontID, SDL_Color color);
	
	void SetText(std::string text);
};

