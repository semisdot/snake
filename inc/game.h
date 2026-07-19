#ifndef GAME_H
#define GAME_H


#include "input.h"
#include "sdl.h"

/* ---------------------------------------------------------------------------------------------------- */

#define GRID_WIDTH		SDL_WINDOW_WIDTH
#define GRID_HEIGHT		SDL_WINDOW_HEIGHT

#define CELL_SIZE		20

#define GRID_ROWS		(GRID_HEIGHT / CELL_SIZE)
#define GRID_COLUMNS	(GRID_WIDTH  / CELL_SIZE)


// snake.h ?
#define SNAKE_MAX_SIZE	(GRID_ROWS * GRID_COLUMNS)
#define SNAKE_INIT_SIZE	3

/* ---------------------------------------------------------------------------------------------------- */

enum // game states
{
	BEGINNING,
	RUNNING,
	END
};

enum
{
	EMPTY,
	FOOD,
	SNAKE
};


struct grid
{
	int cells[GRID_ROWS][GRID_COLUMNS];
};

struct apple
{
	int row, col;
};

struct food
{
	struct apple apple;
};

struct snake_segments
{
	int row, col;
};

struct snake
{
	struct snake_segments segments[SNAKE_MAX_SIZE];
	int head, tail;
	int size;
	int dir_x, dir_y;
};

struct flags
{
	int grid_collision;
	int draw_mem_snake;
	int draw_grid;
};

struct game
{
	struct grid grid;
	struct food food;
	struct snake snake;

	struct flags flags;
	int state;
};

/* ---------------------------------------------------------------------------------------------------- */

void game_state_update(struct events *events, struct game *game, int state);
void game_step(struct events *events, struct game *game);


#endif // GAME_H
