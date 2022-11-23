#pragma once
#include "Component.h"
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2.h"



struct Sprite
{
public:
	SDL_Texture* texture;
	int textureWidth, textureHeight;

	Sprite(SDL_Texture* texture)
	{
		this->texture = texture;
		SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	}
};

class SpriteRenderer : public Component
{
private:
	
	typedef std::map<std::string, Sprite*> TextureMap;
	static TextureMap textureMap;
	
	std::string m_textureID;
	SDL_Texture* texture;

public:
	SpriteRenderer();
	~SpriteRenderer();
	
	void someFunc();
	
	bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void Draw(std::string id, int x, int y, int numberOfCells,int scalerSize, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Animate(std::string id, Vector2 position, int numberOfCells, int scalerSize, int currentRow, int currentFrame, float angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void CursorBlit(SDL_Texture* texture, int x, int y, bool center, SDL_Renderer* renderTarget);

	Sprite* CreateSprite(std::string fileName, std::string id, SDL_Renderer* pRenderer);
};

