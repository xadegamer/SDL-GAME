#pragma once

#include "UIObject.h"
#include "Text.h"

class Slider : public UIObject
{
private:
	
	float value;
	float minValue;
	float maxValue;
	SDL_Rect fillRect;
	Text* text;
	int padding;
		
public:

	std::function <void()> OnClick;
	std::function <void()> OnMouseOver;
	
	Slider(std::string id, Vector2 position, Vector2 size, int padding = 0);
	~Slider() override;

	void Draw() override;
	void Update() override;

	void AddText(std::string id, std::string text, std::string fontID, SDL_Color color);

	inline void SetText(std::string text) { this->text->SetText(text); }

	void SetValue(float value);

	inline float GetValue() { return value; }

};

