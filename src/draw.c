#include <SDL2/SDL.h>

#include "draw.h"

/* ---------------------------------------------------------------------------------------------------- */

static void draw_mem_snake(struct SDL *sdl, struct snake *snake);
static void draw_snake(struct SDL *sdl, struct snake *snake);
static void draw_food(struct SDL *sdl, struct food *food);
static void draw_grid(struct SDL *sdl);
static void draw_grid_border(struct SDL *sdl);

/* ---------------------------------------------------------------------------------------------------- */

void draw(struct SDL *sdl, struct game *game)
{
	if (game->flags.draw_mem_snake)
	{
		draw_mem_snake(sdl, &game->snake);
	}

	draw_food(sdl, &game->food);
	draw_snake(sdl, &game->snake);

	if (game->flags.draw_grid)
	{
		draw_grid(sdl);
	}

	if (game->flags.grid_collision)
	{
		draw_grid_border(sdl);
	}
}

/* ---------------------------------------------------------------------------------------------------- */

static void draw_mem_snake(struct SDL *sdl, struct snake *snake)
{
	SDL_Rect rect;
	int row, col;
	int i;

	rect.w = CELL_SIZE;
	rect.h = CELL_SIZE;

	SDL_SetRenderDrawColor(sdl->renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

	for (i = 0; i < snake->size; ++i)
	{
		int idx = (snake->tail + i) % SNAKE_MAX_SIZE;

		row = idx / GRID_COLUMNS;
		col = idx % GRID_COLUMNS;

		rect.x = col * CELL_SIZE;
		rect.y = row * CELL_SIZE;

		SDL_RenderFillRect(sdl->renderer, &rect);
	}
}

static void draw_snake(struct SDL *sdl, struct snake *snake)
{
	SDL_Rect rect;
	int i;

	rect.w = CELL_SIZE;
	rect.h = CELL_SIZE;

	SDL_SetRenderDrawColor(sdl->renderer, 0, 100, 0, SDL_ALPHA_OPAQUE);

	for (i = 0; i < snake->size; ++i)
	{
		int idx = (snake->tail + i) % SNAKE_MAX_SIZE;

		rect.x = snake->segments[idx].col * CELL_SIZE;
		rect.y = snake->segments[idx].row * CELL_SIZE;

		SDL_RenderFillRect(sdl->renderer, &rect);
	}
}

static void draw_food(struct SDL *sdl, struct food *food)
{
	SDL_Rect rect;

	rect.x = food->apple.col * CELL_SIZE;
	rect.y = food->apple.row * CELL_SIZE;

	rect.w = CELL_SIZE;
	rect.h = CELL_SIZE;

	SDL_SetRenderDrawColor(sdl->renderer, 100, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(sdl->renderer, &rect);
}

static void draw_grid(struct SDL *sdl)
{
	int i;

	SDL_SetRenderDrawColor(sdl->renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);

	for (i = 1; i < GRID_ROWS; ++i)
	{
		SDL_RenderDrawLine(sdl->renderer, 0, i * CELL_SIZE, GRID_WIDTH - 1, i * CELL_SIZE);
	}

	for (i = 1; i < GRID_COLUMNS; ++i)
	{
		SDL_RenderDrawLine(sdl->renderer, i * CELL_SIZE, 0, i * CELL_SIZE, GRID_HEIGHT - 1);
	}
}

static void draw_grid_border(struct SDL *sdl)
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = GRID_WIDTH;
	rect.h = GRID_HEIGHT;

	SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(sdl->renderer, &rect);
}
