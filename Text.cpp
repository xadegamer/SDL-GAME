#include "Text.h"

Text::Text(std::string id, std::string text, std::string fontID, SDL_Color c, Vector2 position, int textSize)
{
	this->ID = id;
	layer = 1;
	this->text = text;
	this->color = c;
	this->font = AssetManager::GetFont(fontID, textSize);
	
	anchorPositon = position;
	
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), surfaceMessage);
	rect = { rect.x, rect.y, surfaceMessage->w, surfaceMessage->h };
	size = Vector2(rect.w, rect.h);
	
	centerPositon = anchorPositon - (size / 2);
	rect.x = centerPositon.x;
	rect.y = centerPositon.y;
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
	
	centerPositon = anchorPositon - (size / 2);
	rect.x = centerPositon.x;
	rect.y = centerPositon.y;

	if(OnTextChange) OnTextChange();
}

void Text::Draw()
{
	SDL_RenderCopy(SDLManager::GetRenderer(), texture, NULL, &rect);	
}

void Text::Update(float deltaTime)
{
	rect.x = centerPositon.x;
	rect.y = centerPositon.y;
}