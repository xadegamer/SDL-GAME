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
		
public:

	
	Slider(std::string id, Vector2 position, Vector2 size);
	~Slider() override;

	void Draw() override;
	void Update(float deltaTime) override;

	void AddText(std::string id, std::string text, std::string fontID, SDL_Color color, int textSize = 32);

	inline void SetText(std::string text) { this->text->SetText(text); }

	void SetValue(float value);

	inline float GetValue() { return value; }

};

