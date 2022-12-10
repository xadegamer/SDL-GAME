#include "SpriteRenderer.h"

#include "Camera.h"

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

void SpriteRenderer::Draw(SDL_Texture* texture, Vector2 position, float angle, SDL_Rect srcRect, SDL_RendererFlip flip, bool relativeToCam)
{
	//Position in world
	destRect.x = position.x;
	destRect.y = position.y;

	if (relativeToCam)
	{
		//Position in camera
		destRect.x -= Camera::GetPosition().x;
		destRect.y -= Camera::GetPosition().y;
	}

	//Size of object
	destRect.w = srcRect.w;
	destRect.h = srcRect.h ;

	SDL_RenderCopyEx(SDLManager::GetRenderer(), texture, &srcRect, &destRect, angle, NULL, flip);
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

void SpriteRenderer::DebugRect()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &destRect);
}
