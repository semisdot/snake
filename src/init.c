#include "init.h"
#include "game.h"

/* ---------------------------------------------------------------------------------------------------- */

static void init_grid(struct grid *grid);
static void init_snake(struct grid *grid, struct snake *snake);

/* ---------------------------------------------------------------------------------------------------- */

void init_game(struct game *game)
{
	init_grid(&game->grid);
	init_snake(&game->grid, &game->snake);
	init_food(&game->grid, &game->food);
}

// TODO
void init_food(struct grid *grid, struct food *food)
{
	static int counter;

	counter = 0;

	while (1)
	{
		food->apple.row = rand() % GRID_ROWS;
		food->apple.col = rand() % GRID_COLUMNS;

		counter += 1;

		if (grid->cells[food->apple.row][food->apple.col] == EMPTY)
		{
			break;
		}
	}

	// printf("INIT FOOD (%d)\n", counter);

	grid->cells[food->apple.row][food->apple.col] = FOOD;
}

/* ---------------------------------------------------------------------------------------------------- */

static void init_grid(struct grid *grid)
{
	memset(grid->cells, 0, sizeof(grid->cells));
}

static void init_snake(struct grid *grid, struct snake *snake)
{
	int i;

	snake->head = SNAKE_INIT_SIZE - 1;
	snake->tail = 0;

	snake->size = SNAKE_INIT_SIZE;

	for (i = 0; i < SNAKE_INIT_SIZE; ++i)
	{
		// init from bottom left corner
		snake->segments[i].row = GRID_ROWS - 1;
		snake->segments[i].col = i;

		grid->cells[GRID_ROWS - 1][i] = SNAKE;
	}

	snake->dir_x = 0;
	snake->dir_y = 0;
}
