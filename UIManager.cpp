#include "UIManager.h"

SDL_Texture* UIManager::messageTexture = nullptr;
SDL_Rect UIManager::messageRect = { 0, 0, 0, 0 };

void UIManager::Init()
{
	TTF_Font* Font = AssetManager::GetFont("Vorgang", 32);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, "Hello World!", { 255, 255, 255, 255 });
	messageTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), surfaceMessage);
	messageRect = { 0, 0, surfaceMessage->w, surfaceMessage->h };
}

void UIManager::Clear()
{
}

void UIManager::DrawMessage(std::string message, int x, int y, int size, SDL_Color color)
{
}

void UIManager::Draw()
{
	SDL_RenderCopy(SDLManager::GetRenderer(), messageTexture, NULL, &messageRect);
}
