#include "SpriteRenderer.h"

SpriteRenderer::TextureMap SpriteRenderer::textureMap{};

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::someFunc()
{

}

bool SpriteRenderer::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{	
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		textureMap[id] = new Sprite(pTexture);

		return true;
	}

	return false;
}

void SpriteRenderer::Draw(std::string id, int x, int y, int numberOfCells, int scalerSize, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
		
	srcRect.w = textureMap[id]->textureWidth / numberOfCells;
	srcRect.h = textureMap[id]->textureHeight;
		
	//Position in world
	destRect.x = x;
	destRect.y = y;
	
	//Size of object
	destRect.w = srcRect.w / scalerSize;
	destRect.h = srcRect.h / scalerSize;
	
	SDL_RenderCopyEx(pRenderer, textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void SpriteRenderer::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = width;
	srcRect.h = height;
	destRect.x = x;
	destRect.y = y;

	//Size of object
	destRect.w = width / 2;
	destRect.h = height / 2;

	SDL_RenderCopyEx(pRenderer, textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void SpriteRenderer::Animate(std::string id, Vector2 position, int numberOfCells, int scalerSize, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = textureMap[id]->textureWidth / numberOfCells * currentFrame;
	srcRect.y = textureMap[id]->textureHeight * (currentRow - 1);
	srcRect.w = textureMap[id]->textureWidth / numberOfCells;
	srcRect.h = textureMap[id]->textureHeight;

	//Position in world
	destRect.x = position.x;
	destRect.y = position.y;

	//Size of object
	destRect.w = srcRect.w / scalerSize;
	destRect.h = srcRect.h / scalerSize;

	SDL_RenderCopyEx(pRenderer, textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void SpriteRenderer::CursorBlit(SDL_Texture* texture, int x, int y, bool center, SDL_Renderer* renderTarget)
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

	SDL_RenderCopy(renderTarget, texture, NULL, &dest);
}
