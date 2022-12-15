#include "TileMap.h"

#include "Camera.h"


TileMap::TileMap(int width, int height, int tileSize)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->numTiles = width * height;
	
	tiles.resize(width);
	for (int i = 0; i < width; i++)
	{
		tiles[i].resize(height);
	}

	grassSprite = AssetManager::GetSprite("grass");
	
	asphaltCentreSprite = AssetManager::GetSprite("Asphalt_Centre");
	asphaltCentreLeftSprite = AssetManager::GetSprite("Asphalt_Centre_Left");
	asphaltCentreRightSprite = AssetManager::GetSprite("Asphalt_Centre_Right");

	LoadMap();
}

TileMap::~TileMap()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			delete tiles[i][j];
		}
	}

	tiles.clear();
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

				tiles[i][j] = new Tile(tileID, GetSprite(tileID));
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
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{			
			SDL_Rect destRect = {x * tileSize - Camera::GetPosition().x, y * tileSize - Camera::GetPosition().y,
			tiles[x][y]->sprite->textureWidth,	tiles[x][y]->sprite->textureHeight};
			SDL_RenderCopy(SDLManager::GetRenderer(), tiles[x][y]->sprite->texture, NULL, &destRect);
		}
	}
}

void TileMap::SaveMaptoFile()
{
	std::string mapPath = "Assets/Maps/Map1.txt";
	std::ofstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				mapFile << tiles[i][j]->id << " ";
			}
			mapFile << std::endl;
		}
		mapFile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

Sprite* TileMap::GetSprite(std::string id)
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

Vector2 TileMap::GetTilePositionById(std::string id)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (tiles[i][j]->id == id)
			{
				return Vector2(i * tileSize, j * tileSize);
			}
		}
	}
	return Vector2(-1, -1);
}
