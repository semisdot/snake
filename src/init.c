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

int init_food(struct grid *grid, struct food *food)
{
	int ret = 0;

	int row, col;
	int row_i, col_i;
	int row_list[GRID_ROWS];
	int col_list[GRID_COLUMNS];
	int row_list_size;
	int col_list_size;
	int i, j;

	row_list_size = GRID_ROWS;

	for (i = 0; i < row_list_size; ++i)
	{
		row_list[i] = i;
	}

	do
	{
		row_i = rand() % row_list_size;
		row = row_list[row_i];

		col_list_size = 0;

		for (j = 0; j < GRID_COLUMNS; ++j)
		{
			if (grid->cells[row][j] == EMPTY)
			{
				col_list[col_list_size++] = j;
			}
		}

		if (col_list_size)
		{
			col_i = rand() % col_list_size;
			col = col_list[col_i];

			food->apple.row = row;
			food->apple.col = col;

			grid->cells[row][col] = FOOD;

			ret = 1;
			break;
		}

		row_list[row_i] = row_list[row_list_size - 1];
		row_list_size -= 1;
	}
	while (row_list_size);

	return ret;
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
