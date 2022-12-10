#pragma once
#include "Component.h"
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2.h"

#include "SDLManager.h"


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
	Sprite* sprite;
	SDL_Rect destRect;

public:
	SpriteRenderer();
	~SpriteRenderer();
	
	void someFunc();

	void SetSprite(Sprite* sprite);

	void Draw(SDL_Texture* texture, Vector2 position, float angle, SDL_Rect srcRect,SDL_RendererFlip flip = SDL_FLIP_NONE, bool relativeToCam = true);
	
	void CursorBlit(SDL_Texture* texture, int x, int y, bool center);

	Sprite* CreateSprite(std::string fileName, std::string id);

	Sprite* GetSprite() { return sprite; }

	
	void DebugRect();
};

