#include <SDL2/SDL.h>

#include "logic.h"
#include "game.h"
#include "init.h"

/* ---------------------------------------------------------------------------------------------------- */

// snake.c ?
static int snake_direction_change(struct events *events, struct game *game)
{
	int ret = 0;

	if (events->keyboard.keys[SDL_SCANCODE_RIGHT] || events->keyboard.keys[SDL_SCANCODE_D])
	{
		game->snake.dir_x = 1;
		game->snake.dir_y = 0;

		ret = 1;
	}
	else if (events->keyboard.keys[SDL_SCANCODE_LEFT] || events->keyboard.keys[SDL_SCANCODE_A])
	{
		game->snake.dir_x = -1;
		game->snake.dir_y = 0;

		ret = 1;
	}
	else if (events->keyboard.keys[SDL_SCANCODE_DOWN] || events->keyboard.keys[SDL_SCANCODE_S])
	{
		game->snake.dir_x = 0;
		game->snake.dir_y = 1;

		ret = 1;
	}
	else if (events->keyboard.keys[SDL_SCANCODE_UP] || events->keyboard.keys[SDL_SCANCODE_W])
	{
		game->snake.dir_x = 0;
		game->snake.dir_y = -1;

		ret = 1;
	}

	return ret;
}

/* ---------------------------------------------------------------------------------------------------- */

void logic(struct events *events, struct game *game)
{
	switch (game->state)
	{
		case BEGINNING:

			if (snake_direction_change(events, game))
			{
				game_state_update(events, game, RUNNING);
			}

			break;

		case RUNNING:

			snake_direction_change(events, game);

			{
				static uint32_t last_update = 0;
				uint32_t now = SDL_GetTicks();

				if (now - last_update >= 200) // 200 ms = 5 updates/sec
				{
					game_step(events, game);

					last_update = now;
				}
			}

			break;

		case END:

			if (snake_direction_change(events, game))
			{
				init_game(game);
				game_state_update(events, game, BEGINNING);
			}

			break;
	}
}

/* ---------------------------------------------------------------------------------------------------- */
