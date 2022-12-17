#include "LayoutTileMap.h"

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h""
#include "Prop.h"
#include "GasCylinder.h"
#include "GroundTileMap.h"
#include "HealthKit.h"

#include "MathUtility.h"

LayoutTileMap::LayoutTileMap(int width, int height, int tileSize, std::string mapPath) : TileMap(width, height, tileSize, mapPath)
{
	DrawMap();
}

LayoutTileMap::~LayoutTileMap()
{
}

void LayoutTileMap::DrawMap()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Vector2 position = Vector2(x * tileSize, y * tileSize);
			PopulateLevel(tiles[x][y]->id, position);
		}
	}
}

void LayoutTileMap::PopulateLevel(std::string id, Vector2 position)
{
	if (id == "E")
	{
		GameObject::Instantiate(new Enemy(position, 100));
	}
	else if (id == "G")
	{
		GameObject::Instantiate(new GasCylinder(position, "BarrelSmall", ColliderType::CIRCLE, SortingLayer::PropsLayer, true, false));
	}
	else if (id == "B")
	{
		int barrelType = MathUtility::RandomRange(1, 3);
		GameObject::Instantiate(new Prop(position, "Barrel_" + std::to_string(barrelType), ColliderType::CIRCLE, SortingLayer::PropsLayer, true, false));
	}
	else if (id == "T")
	{
		// random treee 1 - 6
		int treeType = MathUtility::RandomRange(1, 6);
		GameObject::Instantiate(new Prop(position, "Tree_" + std::to_string(treeType), ColliderType::None, SortingLayer::TreesLayer, true, false));
	}
	else if (id == "C")
	{
		// random car 1 - 2
		int carType = MathUtility::RandomRange(1, 3);
		GameObject::Instantiate(new Prop(position, "Car_" + std::to_string(carType), ColliderType::BOX, SortingLayer::PropsLayer, true, false));
	}
	else if (id == "H")
	{
		GameObject::Instantiate(new HealthKit(position, "HeathKit", ColliderType::BOX, SortingLayer::CollectableLayer, 50));
	}
	else if (id == "P")
	{
		playerPosition = position;
	}
}

