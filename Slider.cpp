#include "Slider.h"

Slider::Slider(std::string id, Vector2 position, Vector2 size, int padding)
{
	ID = id;
	value = 0;
	minValue = 0;
	maxValue = 1;

	layer = 0;
	anchorPositon = position;
	this->size = size;
	this->padding = padding;

	size.x += padding;
	size.y += padding;

	centerPositon = anchorPositon - (size / 2);
	rect = { (int)centerPositon.x, (int)centerPositon.y, (int)size.x , (int)size.y };
	fillRect = { (int)centerPositon.x, (int)centerPositon.y, (int)size.x - 20 , (int)size.y - 20 };
}

Slider::~Slider()
{
	if (text != nullptr) delete text;
}

void Slider::Draw()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 0, 255);	
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &rect);
	SDL_RenderFillRect(SDLManager::GetRenderer(), &rect);

	fillRect = { (int)centerPositon.x, (int)centerPositon.y, (int)(size.x * value), (int)size.y };

	if (value != 0)
	{
		SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255 - (int)(255 * value), (int)(255 * value), 0, 255);
		SDL_RenderDrawRect(SDLManager::GetRenderer(), &fillRect);
		SDL_RenderFillRect(SDLManager::GetRenderer(), &fillRect);
	}

	if (text != nullptr) text->Draw();
}

void Slider::Update()
{
	
}

void Slider::AddText(std::string id,std::string text, std::string fontID, SDL_Color color, int textSize)
{
	this->text = new Text(id, text, fontID, color, Vector2(centerPositon.x + size.x / 2, centerPositon.y + size.y / 2),textSize);
}

void Slider::SetValue(float value)
{
	this->value = MathUtility::Clamp(value, minValue, maxValue);
}
