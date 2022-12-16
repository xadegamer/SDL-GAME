#include "Image.h"

Image::Image(std::string ID, std::string imageID, Vector2 anchorPositon)
{
	this->ID = ID;
	sprite = AssetManager::GetSprite(imageID);
	this->anchorPositon = anchorPositon;
	centerPositon = anchorPositon + Vector2(sprite->textureWidth / 2, sprite->textureHeight / 2);
	rect = { (int)anchorPositon.x, (int)anchorPositon.y, sprite->textureWidth, sprite->textureHeight };
}

Image::~Image()
{
	
}

void Image::Draw()
{
	SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &rect);
}

void Image::Update()
{
	
}
