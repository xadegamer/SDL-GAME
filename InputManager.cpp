#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr) instance = new InputManager();
	return instance;
}

void InputManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

InputManager::InputManager()
{
	currentKeyboardState = SDL_GetKeyboardState(&keyLength);
	previousKeyboardState = new Uint8[keyLength];
	memcpy(previousKeyboardState, currentKeyboardState, keyLength);
}

InputManager::~InputManager()
{
	delete[] previousKeyboardState;
	previousKeyboardState = nullptr;
}

bool InputManager::GetKey(SDL_Scancode key)
{
	return currentKeyboardState[key];
}

bool InputManager::GetKeyDown(SDL_Scancode key)
{
	return !previousKeyboardState[key] && currentKeyboardState[key];
}

bool InputManager::GetKeyUp(SDL_Scancode key)
{
	return previousKeyboardState[key] && !currentKeyboardState[key];
}

bool InputManager::GetMouseButtonDown(MOUSE_BUTTON button)
{
	Uint32 mask = 0;
	
	switch (button)
	{
		case InputManager::LEFT:mask = SDL_BUTTON_LMASK;break;
		case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK;break;
		case InputManager::RIGHT:mask = SDL_BUTTON_RMASK;break;
		case InputManager::BACK:mask = SDL_BUTTON_X1MASK;break;
		case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK;break;
	}
	
	return (currentMouseState & mask);
}

bool InputManager::GetMouseButton(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
		case InputManager::LEFT:mask = SDL_BUTTON_LMASK; break;
		case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK; break;
		case InputManager::RIGHT:mask = SDL_BUTTON_RMASK; break;
		case InputManager::BACK:mask = SDL_BUTTON_X1MASK; break;
		case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK; break;
	}

	return !(previousMouseState & mask) && (currentMouseState & mask);
}

bool InputManager::GetMouseButtonUp(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
		case InputManager::LEFT:mask = SDL_BUTTON_LMASK; break;
		case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK; break;
		case InputManager::RIGHT:mask = SDL_BUTTON_RMASK; break;
		case InputManager::BACK:mask = SDL_BUTTON_X1MASK; break;
		case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK; break;
	}

	return (previousMouseState & mask) && !(currentMouseState & mask);
}


Vector2 InputManager::GetMousePosition()
{
	return Vector2{ (float)mouseX, (float)mouseY };
}

void InputManager::Update()
{
	currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

void InputManager::UpdatePreviousInput()
{
	memcpy(previousKeyboardState, currentKeyboardState, keyLength);
	previousMouseState = currentMouseState;
}
