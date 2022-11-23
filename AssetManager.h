#pragma once
#include <iostream>
#include <map>
#include "SDL.h"

class AssetManager
{
private:

	static AssetManager* instance;

	std::map<std::string, SDL_Texture*> textures;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename);

private:

	AssetManager();
	~AssetManager();

};

