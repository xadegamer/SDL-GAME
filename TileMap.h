#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include <map>

#include <fstream>
#include <iostream>
#include <string>

#include <vector>

struct Tile
{
	std::string id;
	Sprite* sprite;

	Tile(std::string id, Sprite* sprite)
	{
		this->id = id;
		this->sprite = sprite;
	}
};

class TileMap
{
private:
	
	int width;
	int height;
	int tileSize;
	int numTiles;

	std::vector<std::vector<Tile*>> tiles;
	
	Sprite* grassSprite;
	
	Sprite* asphaltTopLeftSprite;
	Sprite* asphaltTopCentreSprite;
	Sprite* asphaltTopRightSprite;
	
	Sprite* asphaltCentreLeftSprite;
	Sprite* asphaltCentreSprite;
	Sprite* asphaltCentreRightSprite;

	Sprite* asphaltBottomLeftSprite;
	Sprite* asphaltBottomCentreSprite;
	Sprite* asphaltBottomRightSprite;
	
public:
	TileMap(int width, int height, int tileSize);
	~TileMap();

	void LoadMap();
	void DrawMap();
	void SaveMaptoFile();

	Sprite* GetSprite(std::string id);

	Vector2 GetTilePositionById(std::string id);
};

