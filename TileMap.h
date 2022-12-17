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
	Tile(std::string id)
	{
		this->id = id;
	}
};

class TileMap
{
protected:
	
	int width;
	int height;
	int tileSize;
	int numTiles;

	std::vector<std::vector<Tile*>> tiles;
	
public:
	TileMap(int width, int height, int tileSize, std::string mapPath);
	~TileMap();

	void LoadMap(std::string mapPath);
	virtual void DrawMap() {};
	void SaveMaptoFile(std::string mapPath = "Assets/Maps/Map1.txt");

	Vector2 GetTilePositionById(std::string id);
};

