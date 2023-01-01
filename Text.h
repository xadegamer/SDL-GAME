#pragma once

#include "UIObject.h"


class Text : public UIObject
{
	
private:
	std::string text;
	SDL_Color color;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;

	std::function <void()> onTextChange;
public:

	Text(std::string id, std::string text, std::string fontID, SDL_Color c, Vector2 position, int textSize = 32);
	~Text() override;

	void Draw() override;
	void Update(float deltaTime) override;

	inline std::function <void()>& OnTextChange() { return onTextChange; }

	void SetText(std::string text);
};

