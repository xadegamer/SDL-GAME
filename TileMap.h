#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include <map>

#include <fstream>
#include <iostream>
#include <string>


struct Tile
{
	std::string id;
};

class TileMap
{
private:
	
	int width;
	int height;
	int tileSize;
	int numTiles;
	
	Tile** tiles;

	Sprite* grassSprite;
	Sprite* asphaltSprite;

	
public:
	TileMap(int width, int height, int tileSize);
	~TileMap();

	void LoadMap();
	void DrawMap();
	void SaveMaptoFile();
};

