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

	grassSprite = AssetManager::GetSprite("Grass");
	asphaltSprite = AssetManager::GetSprite("Asphalt");
	
	LoadMap();
}

TileMap::~TileMap()
{
	for (int i = 0; i < width; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
}

void TileMap::LoadMap()
{
	std::string mapPath = "Assets/Maps/Map1.txt";
	std::ifstream mapFile(mapPath);

	if (mapFile.is_open())
	{
		// load the file to the map
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				std::string tileID;
				mapFile >> tileID;
				tiles[i][j].id = tileID;
			}
		}
		mapFile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void TileMap::DrawMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{ 
			Sprite* sprite = tiles[x][y].id == "S" ? grassSprite : asphaltSprite;
			
			SDL_Rect destRect = 
			{
			x * tileSize - Camera::GetPosition().x,
			y* tileSize - Camera::GetPosition().y,
			sprite->textureWidth,
			sprite->textureHeight
			};
			SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect);
		}
	}
}

void TileMap::SaveMaptoFile()
{
	std::string mapPath = "Assets/Maps/Map1.txt";
	std::ofstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				mapFile << tiles[x][y].id << " ";
			}
			mapFile << std::endl;
		}
	}
}
