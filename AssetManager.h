#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "SpriteRenderer.h"

#include "SDLManager.h"

class AssetManager
{
private:
	static std::map<std::string, Sprite*> sprites;

	static std::map<std::string, TTF_Font*> fonts;
	
	static std::map<std::string, Mix_Chunk*> sounds;
	
	static std::map<std::string, Mix_Music*> musics;
	
public:

	static void Init();
	static void Clear();
	
	static Sprite* GetSprite(std::string filename);
	
	static TTF_Font* GetFont(std::string filename, int size);

	static Mix_Chunk* GetSound(std::string filename);

	static Mix_Music* GetMusic(std::string filename);

private:
	AssetManager() = delete;
	~AssetManager() = delete;
};

