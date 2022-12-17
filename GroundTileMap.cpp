#include "GroundTileMap.h"

#include "Camera.h"

GroundTileMap::GroundTileMap(int width, int height, int tileSize, std::string mapPath) : TileMap(width, height, tileSize, mapPath)
{
	grassSprite = AssetManager::GetSprite("grass");
	asphaltCentreSprite = AssetManager::GetSprite("Asphalt_Centre");
	asphaltCentreLeftSprite = AssetManager::GetSprite("Asphalt_Centre_Left");
	asphaltCentreRightSprite = AssetManager::GetSprite("Asphalt_Centre_Right");
}

GroundTileMap::~GroundTileMap()
{
}

void GroundTileMap::DrawMap()
{
	Sprite* sprite = nullptr;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			sprite = GetSprite(tiles[x][y]->id);
			SDL_Rect destRect = { x * tileSize - Camera::GetPosition().x, y * tileSize - Camera::GetPosition().y, sprite->textureWidth,	sprite->textureHeight };
			SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect);
		}
	}
}

Sprite* GroundTileMap::GetSprite(std::string id)
{	
	if (id == "F")
	{
		return grassSprite;
	}
	else if (id == "S")
	{
		return asphaltCentreSprite;
	}
	else if (id == "L")
	{
		return asphaltCentreLeftSprite;
	}
	else if (id == "R")
	{
		return asphaltCentreRightSprite;
	}
	else
	{
		return grassSprite;
	}
}
