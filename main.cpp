#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "InputManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Game.h"


using namespace std;

#define PI 3.14159265358979323846

InputManager* inputmanager;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

float GetAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

void CursorBlit(SDL_Texture* texture, int x, int y, bool center, SDL_Renderer* renderTarget)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(renderTarget, texture, NULL, &dest);
}

void blitRotated(SDL_Texture* texture, int x, int y, float angle, SDL_Renderer* renderTarget)
{
	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = dstRect.h = 100;
	SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	SDL_RenderCopyEx(renderTarget, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void ToggleCursor(bool show)
{
	SDL_ShowCursor(show);
}

SDL_Texture* loadSurface(std::string path, SDL_Renderer* renderTarget)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (!loadedSurface == NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderTarget, loadedSurface);

		if (!newTexture == NULL)
		{
			SDL_FreeSurface(loadedSurface);
		}
		else
		{
			cout << "Unable to create texture from %s! SDL Error:" << SDL_GetError();
		}
	}
	else
	{
		cout << "Unable to load image %s! SDL_image Error:" << IMG_GetError();
	}
	
	return newTexture;
}


int OldMain(int arg, char* argv[])
{
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* renderTarget = nullptr;

	SDL_Texture* imageTexture = nullptr;

	SDL_Texture* cursorTexture = nullptr;

	SDL_Rect playerRect;
	SDL_Rect playerPosition;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	playerPosition.x = playerPosition.y = 100;
	playerPosition.w = playerPosition.h = 100;

	Uint32 previousFrameTicks = SDL_GetTicks();
	float deltaTime = 0;

	Uint32 frameStart, frameTime;


	float moveSpeed = 3.0f;

	int mouse_x, mouse_y;

	const Uint8* keyState;

	SDL_Init(SDL_INIT_EVERYTHING);

	//Initialize PNG loading
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		cout << "SDL_image could not initialize!SDL_image Error :" << IMG_GetError();
	}
	else
	{
		//Get window surface
	}

	sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);

	renderTarget = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	imageTexture = loadSurface("Assets/Character.png", renderTarget);

	cursorTexture = loadSurface("Assets/Cursor.png", renderTarget);

	SDL_QueryTexture(imageTexture, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 6;
	frameHeight = textureWidth / 1;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	bool isRunning = true;
	SDL_Event ev;

	inputmanager = inputmanager->GetInstance();

	GameObject* newObject = new GameObject();
	newObject->AddComponent<SpriteRenderer>();

	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		inputmanager->Update();

		inputmanager->UpdatePreviousInput();

		SDL_GetMouseState(&mouse_x, &mouse_y);

		while (SDL_PollEvent(&ev) != 0)
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_MOUSEMOTION:
				//playerPosition.x = mouse_x - playerPosition.w / 2;
				//playerPosition.y = mouse_y - playerPosition.h / 2;
				cout << "Mouse x:" << mouse_x << " : Mouse y: " << mouse_y << endl;
				break;
			default:break;
			}
		}

		if (inputmanager->GetKey(SDL_SCANCODE_UP))
		{
			cout << "Up" << endl;
			playerPosition.y -= moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_DOWN))
		{
			cout << "Down" << endl;
			playerPosition.y += moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_LEFT))
		{
			cout << "Left" << endl;
			playerPosition.x -= moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_RIGHT))
		{
			cout << "Right" << endl;
			playerPosition.x += moveSpeed;
		}

		//Player animation
		playerRect.x = frameWidth * int(((SDL_GetTicks() / 100) % 6));

		SDL_RenderClear(renderTarget);

		CursorBlit(cursorTexture, mouse_x, mouse_y, true, renderTarget);

		SDL_RenderCopyEx(renderTarget, imageTexture, &playerRect, &playerPosition, GetAngle(mouse_x, mouse_y, playerPosition.x, playerPosition.y), NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderTarget);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) SDL_Delay((int)(DELAY_TIME - frameTime));
	}

	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(sdlWindow);
	renderTarget = nullptr;
	sdlWindow = nullptr;

	SDL_Quit();

	return 0;
}

int main(int arg, char* argv[])
{
	Uint32 frameStart, frameTime;
	float moveSpeed = 1.0f;
	
	frameStart = SDL_GetTicks();
	
	Game* g_game = new Game();

	g_game->Init("Chapter 1", 100, 100, 1280, 720, false);

	inputmanager = inputmanager->GetInstance();

	while (g_game->IsRunning())
	{
		g_game->HandleEvents();
		g_game->Update();
		g_game->Render();
		
		inputmanager->Update();
		inputmanager->UpdatePreviousInput();

		if (inputmanager->GetKey(SDL_SCANCODE_UP))
		{
			cout << "Up" << endl;
			g_game->player.ModifyPosition()->y -= moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_DOWN))
		{
			cout << "Down" << endl;
			g_game->player.ModifyPosition()->y += moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_LEFT))
		{
			cout << "Left" << endl;
			g_game->player.ModifyPosition()->x -= moveSpeed;
		}

		if (inputmanager->GetKey(SDL_SCANCODE_RIGHT))
		{
			g_game->player.ModifyPosition()->x += moveSpeed;
		}


		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) SDL_Delay((int)(DELAY_TIME - frameTime));
	}
	g_game->Clean();

	
//	OldMain(arg, argv);
		
	return 0;
}
