#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::someFunc()
{

}

void SpriteRenderer::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::Draw(SDL_Texture* texture, Vector2 position, int scalerSize, float angle, SDL_Rect srcRect, SDL_RendererFlip flip)
{
	//Position in world
	destRect.x = position.x;
	destRect.y = position.y;

	//Size of object
	destRect.w = srcRect.w / scalerSize;
	destRect.h = srcRect.h / scalerSize;
	
	//set pivot point
	SDL_Point* pivot = new SDL_Point();
	pivot->x = destRect.w / 2;
	pivot->y = destRect.h / 2;

	SDL_RenderCopyEx(SDLManager::GetRenderer(), texture, &srcRect, &destRect, angle, pivot, flip);
}

void SpriteRenderer::CursorBlit(SDL_Texture* texture, int x, int y, bool center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(SDLManager::GetRenderer(), texture, NULL, &dest);
}

Sprite* SpriteRenderer::CreateSprite(std::string fileName, std::string id)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) return nullptr;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) return new Sprite(pTexture);
	else return nullptr;
}
