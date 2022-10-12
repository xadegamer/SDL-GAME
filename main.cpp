#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

SDL_Texture* LoadTexture(string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

	if (surface == NULL)
	{
		cout << "Error:" << SDL_GetError() << endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
		{
			cout << "Error:" << SDL_GetError() << endl;
		}
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int arg, char* argv[])
{
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	SDL_Texture* currentImage = nullptr;
	SDL_Rect playerRect;
	SDL_Rect playerPosition;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 32;

	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	float moveSpeed = 5000.0f;

	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());

	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	else
	{
		//Get window surface
		SDL_Surface* gScreenSurface = SDL_GetWindowSurface(sdlWindow);
	}

	sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);
	renderTarget = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	currentImage = LoadTexture("Assets/door.bmp", renderTarget);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureWidth / 4;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)isRunning = false;
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RIGHT:
					playerPosition.x += moveSpeed * deltaTime;
					break;

				case SDLK_LEFT:
					playerPosition.x -= moveSpeed * deltaTime;
					break;

				case SDLK_UP:
					playerPosition.y -= moveSpeed * deltaTime;
					break;

				case SDLK_DOWN:
					playerPosition.y += moveSpeed * deltaTime;
					break;

				default: break;
				}
			}
		}

		frameTime += deltaTime;

		if (frameTime >= 0.25f)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textureWidth) playerRect.x = 0;
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(currentImage);
	SDL_DestroyWindow(sdlWindow);
	renderTarget = nullptr;
	currentImage = nullptr;
	sdlWindow = nullptr;

	SDL_Quit();

	return 0;
}