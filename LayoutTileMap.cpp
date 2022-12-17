#include "LayoutTileMap.h"

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h""
#include "Prop.h"
#include "GasCylinder.h"
#include "GroundTileMap.h"
#include "HealthKit.h"

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
		GameObject::Instantiate(new GasCylinder(position, "BarrelSmall", ColliderType::CIRCLE, 1, true, false));
	}
	else if (id == "T")
	{
		GameObject::Instantiate(new Prop(position, "Tree_3", ColliderType::None, 3, true, false));
	}
	else if (id == "C")
	{
		GameObject::Instantiate(new Prop(Vector2(900, 500), "Car_1", ColliderType::BOX, 2, true, false));
	}
	else if (id == "H")
	{
		GameObject::Instantiate(new HealthKit(position, "HeathKit", ColliderType::BOX, 1, 50));
	}
	else if (id == "P")
	{
		playerPosition = position;
	}
}

