#include "Image.h"

Image::Image(std::string ID, std::string imageID, Vector2 anchorPositon)
{
	this->ID = ID;

	spriteRenderer.SetSprite(AssetManager::GetSprite(imageID));

	this->anchorPositon = anchorPositon;
	centerPositon = anchorPositon - Vector2(spriteRenderer.GetSprite()->textureWidth / 2, spriteRenderer.GetSprite()->textureHeight / 2);
	rect = { (int)centerPositon.x, (int)centerPositon.y, spriteRenderer.GetSprite()->textureWidth, spriteRenderer.GetSprite()->textureHeight };
}

Image::~Image()
{

}

void Image::Update(float deltaTime)
{

}

void Image::Draw()
{
	spriteRenderer.Draw(rect);
}
