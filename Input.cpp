
#include "Common.h"

#include "Input.h"


void Input::doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			//doKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			//doKeyUp(&event.key);
			break;

		default:
			break;
		}
	}

	//SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}

