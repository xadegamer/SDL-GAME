#include "Text.h"

Text::Text(std::string text, std::string fontID, SDL_Color c, Vector2 position)
{
	layer = 1;
	this->text = text;
	this->color = c;
	this->font = AssetManager::GetFont(fontID, 32);
	
	origin = position;
	
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), surfaceMessage);
	rect = { rect.x, rect.y, surfaceMessage->w, surfaceMessage->h };
	size = Vector2(rect.w, rect.h);
	
	transform->position = origin - (size / 2);
	rect.x = transform->position.x;
	rect.y = transform->position.y;
}

Text::~Text()
{
	SDL_FreeSurface(surfaceMessage);
}

void Text::SetText(std::string text)
{
	this->text = text;
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), surfaceMessage);
	rect = { rect.x, rect.y, surfaceMessage->w, surfaceMessage->h };
	size = Vector2(rect.w, rect.h);
	
	transform->position = origin - (size / 2);
	rect.x = transform->position.x;
	rect.y = transform->position.y;

	if(OnTextChange) OnTextChange();
}

void Text::Draw()
{
	SDL_RenderCopy(SDLManager::GetRenderer(), texture, NULL, &rect);	
}

void Text::Update()
{
	rect.x = transform->position.x;
	rect.y = transform->position.y;
}