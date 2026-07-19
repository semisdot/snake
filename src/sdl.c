#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_sdl(struct SDL *sdl)
{
	if (SDL_Init(SDL_INIT_FLAGS) != 0)
	{
		SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit);

#if 0
	if ((IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS) != IMG_INIT_FLAGS)
	{
		SDL_Log("Could not initialize IMG: %s\n", IMG_GetError());
		exit(1);
	}

	atexit(IMG_Quit);
#endif

	sdl->window = SDL_CreateWindow(SDL_WINDOW_TITLE,
								   SDL_WINDOW_X,
								   SDL_WINDOW_Y,
								   SDL_WINDOW_WIDTH,
								   SDL_WINDOW_HEIGHT,
								   SDL_WINDOW_FLAGS);

	if (!sdl->window)
	{
		SDL_Log("Could not create SDL window: %s\n", SDL_GetError());
		exit(1);
	}

	sdl->renderer = SDL_CreateRenderer(sdl->window,
									   SDL_RENDERER_INDEX,
									   SDL_RENDERER_FLAGS);

	if (!sdl->renderer)
	{
		SDL_Log("Could not create SDL renderer: %s\n", SDL_GetError());
		exit(1);
	}
}
