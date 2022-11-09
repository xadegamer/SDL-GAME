#pragma once

#include <iostream>
#include <typeinfo>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

class Component
{
public:
	std::string name;

	virtual void someFunc();;
};

