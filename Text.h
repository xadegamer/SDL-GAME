#pragma once

#include "UIObject.h"


class Text : public UIObject
{
	
public:
	
	std::string text;
	SDL_Color color;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;
	Vector2 origin;

	//ontextchange event
	std::function <void()> OnTextChange;
	
	Text(std::string text, std::string fontID, SDL_Color c, Vector2 position);
	~Text() override;

	void Draw() override;
	void Update() override;

	void SetText(std::string text);
};

