#include "TileMap.h"

#include "Camera.h"

TileMap::TileMap(int width, int height, int tileSize)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->numTiles = width * height;
	this->tiles = new Tile * [width];
	for (int i = 0; i < width; i++)
	{
		this->tiles[i] = new Tile[height];
	}
}

TileMap::~TileMap()
{
	for (int i = 0; i < width; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
}

void TileMap::LoadMap(std::string mapPath)
{
	// load random map for now
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tiles[i][j].id = rand() % 3;
			tiles[i][j].position = Vector2(i * tileSize, j * tileSize);
			tiles[i][j].sprite = SpriteRenderer::CreateSprite("Assets/Textures/Tile.png", "Tile");
		}
	}
	
	
	//std::ifstream mapFile;
	//mapFile.open(mapPath);
	//if (mapFile.is_open())
	//{
	//	for (int y = 0; y < height; y++)
	//	{
	//		for (int x = 0; x < width; x++)
	//		{
	//			int tileID;
	//			mapFile >> tileID;
	//			tiles[x][y].id = tileID;
	//			tiles[x][y].position = Vector2(x * tileSize, y * tileSize);
	//			tiles[x][y].sprite = new Sprite("Tileset.png", Vector2(tileSize, tileSize), Vector2(tileSize * tileID, 0));
	//		}
	//	}
	//}
	//mapFile.close();
}

void TileMap::DrawMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{ 
			Sprite* sprite = tiles[x][y].sprite;
			Vector2 position = tiles[x][y].position;
			SDL_Rect destRect = 
			{
			position.x - Camera::GetPosition().x,
			position.y - Camera::GetPosition().y,
			sprite->textureWidth,
			sprite->textureHeight
			};
			SDL_RenderCopy(SDLManager::GetRenderer(), tiles[x][y].sprite->texture, NULL, &destRect);
		}
	}
}
