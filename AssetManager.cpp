#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (instance == nullptr) instance = new AssetManager();

	return instance;
}

void AssetManager::Release()
{
	delete instance;
	instance = nullptr;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto tex : textures)
	{
		if (tex.second != nullptr)
		{
			SDL_DestroyTexture(tex.second);
		}
	}
	textures.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	//if (textures[fullPath] == nullptr)
	//{
	//	textures[fullPath] = Gph
	//}

	return nullptr;
}
