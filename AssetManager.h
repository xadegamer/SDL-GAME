#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "SpriteRenderer.h"


class AssetManager
{
private:
	static std::map<std::string, Sprite*> sprites;

public:
	static Sprite* GetSprite(std::string filename);

private:
	AssetManager() = delete;
	~AssetManager() = delete;

	static void Init();
	static void Clear();
};

