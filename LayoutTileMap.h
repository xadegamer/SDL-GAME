#pragma once

#include "TileMap.h"

class LayoutTileMap : public TileMap
{	
private:
	Vector2 playerPosition;


public:
	LayoutTileMap(int width, int height, int tileSize, std::string mapPath);
	~LayoutTileMap();

	void DrawMap() override;

	void PopulateLevel(std::string id, Vector2 position);

	Vector2 GetPlayerPosition() { return playerPosition; }
};
