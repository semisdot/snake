#ifndef SDL_H
#define SDL_H


#include <SDL2/SDL.h>

/* ---------------------------------------------------------------------------------------------------- */

#define SDL_INIT_FLAGS		SDL_INIT_VIDEO
#define IMG_INIT_FLAGS		IMG_INIT_PNG

#define SDL_WINDOW_TITLE	"snake"
#define SDL_WINDOW_X		SDL_WINDOWPOS_CENTERED
#define SDL_WINDOW_Y		SDL_WINDOWPOS_CENTERED
#define SDL_WINDOW_WIDTH	320
#define SDL_WINDOW_HEIGHT	200
#define SDL_WINDOW_FLAGS	0

#define SDL_RENDERER_INDEX	-1
#define SDL_RENDERER_FLAGS	SDL_RENDERER_ACCELERATED

/* ---------------------------------------------------------------------------------------------------- */

struct SDL
{
	SDL_Window	 *window;
	SDL_Renderer *renderer;
};

/* ---------------------------------------------------------------------------------------------------- */

void init_sdl(struct SDL *sdl);


#endif // SDL_H
