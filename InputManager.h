#pragma once

#define _INPUTMANAGER
#include "Helper.h"
#include "Vector2.h"

class InputManager
{
private:
	static InputManager* instance;
	
	Uint8* previousKeyboardState = nullptr;
	const Uint8* currentKeyboardState = nullptr;
	int keyLength = 0;

	Uint32 previousMouseState = 0;
	Uint32 currentMouseState = 0;
	
	int mouseX = 0;
	int mouseY = 0;
	
public:
	enum MOUSE_BUTTON { LEFT = 0, MIDDLE = 1, RIGHT = 2, BACK = 3, FORWARD = 4 };
	
	InputManager();
	~InputManager();
	
	static InputManager* GetInstance();
	static void ReleaseInstance();

	bool GetKeyDown(SDL_Scancode key);
	bool GetKey(SDL_Scancode key);
	bool GetKeyUp(SDL_Scancode key);


	bool GetMouseButtonDown(MOUSE_BUTTON button);
	bool GetMouseButton(MOUSE_BUTTON button);
	bool GetMouseButtonUp(MOUSE_BUTTON button);
	
	Vector2 GetMousePosition();
	
	void Update();
	void UpdatePreviousInput();
};

