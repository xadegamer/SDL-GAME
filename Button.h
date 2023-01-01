#pragma once

#include "UIObject.h"
#include "Text.h"

enum class buttonState { DEFAULT, HOVERED, PRESSED };

class Button : public UIObject
{
	
protected:
	
	buttonState currentState;
	Text* text;
	std::function <void()> onClick;
	std::function <void()> onMouseOver;
	
public:
	
	Button(std::string id, Vector2 position, Vector2 size);
	~Button() override;

	void Draw() override;
	void Update(float deltaTime) override;
	
	inline std::function <void()>& OnClick() { return onClick; }

	inline std::function <void()>& OnMouseOver() { return onMouseOver; }

	void AddText(std::string id,std::string text, std::string fontID, SDL_Color color);
	
	void SetText(std::string text);
};

