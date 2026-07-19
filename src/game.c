
#include "game.h"
#include "init.h"

/* ---------------------------------------------------------------------------------------------------- */

static int grid_collision(struct snake_segments *next_head);
static int food_collision(struct grid *grid, struct snake_segments *next_head);
static int snake_max_size(struct snake *snake);
static int snake_collision(struct grid *grid, struct snake_segments *next_head, struct snake_segments *curr_tail);

/* ---------------------------------------------------------------------------------------------------- */

void game_state_update(struct events *events, struct game *game, int state)
{
	memset(events->keyboard.keys, 0, sizeof(events->keyboard.keys));
	game->state = state;
}

void game_step(struct events *events, struct game *game)
{
	struct snake *snake;
	struct snake_segments curr_tail;
	struct snake_segments next_head;

	snake = &game->snake;

	curr_tail.row = snake->segments[snake->tail].row;
	curr_tail.col = snake->segments[snake->tail].col;

	next_head.row = snake->segments[snake->head].row + snake->dir_y;
	next_head.col = snake->segments[snake->head].col + snake->dir_x;

	if (grid_collision(&next_head))
	{
		if (game->flags.grid_collision)
		{
			game_state_update(events, game, END);
			// printf("GRID COLLISION\n");
			return;
		}
		else
		{
			// wrap around
			next_head.row = (next_head.row + GRID_ROWS) % GRID_ROWS;
			next_head.col = (next_head.col + GRID_COLUMNS) % GRID_COLUMNS;
		}
	}

	if (snake_collision(&game->grid, &next_head, &curr_tail))
	{
		game_state_update(events, game, END);
		// printf("SNAKE COLLISION\n");
		return;
	}

	if (food_collision(&game->grid, &next_head))
	{
		snake->size += 1;

		if (snake_max_size(snake))
		{
			game_state_update(events, game, END);
			// printf("SNAKE MAX SIZE\n");
		}
		else
		{
			init_food(&game->grid, &game->food);
		}
	}
	else
	{
		// update snake tail index
		snake->tail = (snake->tail + 1) % SNAKE_MAX_SIZE;

		game->grid.cells[curr_tail.row][curr_tail.col] = EMPTY;
	}

	// update snake head index
	snake->head = (snake->head + 1) % SNAKE_MAX_SIZE;

	snake->segments[snake->head].row = next_head.row;
	snake->segments[snake->head].col = next_head.col;

	game->grid.cells[next_head.row][next_head.col] = SNAKE;
}

/* ---------------------------------------------------------------------------------------------------- */

static int grid_collision(struct snake_segments *next_head)
{
	int ret = 0;

	if (next_head->row < 0 || next_head->row == GRID_ROWS || next_head->col < 0 || next_head->col == GRID_COLUMNS)
	{
		ret = 1;
	}

	return ret;
}

static int food_collision(struct grid *grid, struct snake_segments *next_head)
{
	int ret = 0;

	if (grid->cells[next_head->row][next_head->col] == FOOD)
	{
		ret = 1;
	}

	return ret;
}

static int snake_max_size(struct snake *snake)
{
	int ret = 0;

	if (snake->size == SNAKE_MAX_SIZE)
	{
		ret = 1;
	}

	return ret;
}

static int snake_collision(struct grid *grid, struct snake_segments *next_head, struct snake_segments *curr_tail)
{
	int ret = 0;

	if (grid->cells[next_head->row][next_head->col] == SNAKE)
	{
		// allow snake's head collision with tail
		if (!(next_head->row == curr_tail->row && next_head->col == curr_tail->col))
		{
			ret = 1;
		}
	}

	return ret;
}
