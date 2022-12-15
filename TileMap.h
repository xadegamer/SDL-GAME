#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"

struct Tile
{
	int id;
	Sprite* sprite;
	Vector2 position;
};

class TileMap
{
private:
	
	int width;
	int height;
	int tileSize;
	int numTiles;
	Tile** tiles;

	
public:
	TileMap(int width, int height, int tileSize);
	~TileMap();

	void LoadMap(std::string mapPath);
	void DrawMap();
};

