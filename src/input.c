#include <SDL2/SDL.h>

#include "input.h"

/* ---------------------------------------------------------------------------------------------------- */

static void key_down(SDL_KeyboardEvent *event, struct keyboard *keyboard);
static void key_up(SDL_KeyboardEvent *event, struct keyboard *keyboard);
// static void mouse_button_down(SDL_MouseButtonEvent *event, struct mouse *mouse);
// static void mouse_button_up(SDL_MouseButtonEvent *event, struct mouse *mouse);

/* ---------------------------------------------------------------------------------------------------- */

void input(struct events *events)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				// break;

			case SDL_KEYDOWN:
				key_down(&event.key, &events->keyboard);
				break;

			case SDL_KEYUP:
				key_up(&event.key, &events->keyboard);
				break;
#if 0
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&events->mouse.x, &events->mouse.y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_button_down(&event.button, &events->mouse);
				break;

			case SDL_MOUSEBUTTONUP:
				mouse_button_up(&event.button, &events->mouse);
				break;
#endif
		}
	}
}

/* ---------------------------------------------------------------------------------------------------- */

static void key_down(SDL_KeyboardEvent *event, struct keyboard *keyboard)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		keyboard->keys[event->keysym.scancode] = 1;
	}
}

static void key_up(SDL_KeyboardEvent *event, struct keyboard *keyboard)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		keyboard->keys[event->keysym.scancode] = 0;
	}
}

#if 0
static void mouse_button_down(SDL_MouseButtonEvent *event, struct mouse *mouse)
{
	if (event->button < MAX_MOUSE_BUTTONS)
	{
		mouse->buttons[event->button] = 1;
	}
}

static void mouse_button_up(SDL_MouseButtonEvent *event, struct mouse *mouse)
{
	if (event->button < MAX_MOUSE_BUTTONS)
	{
		mouse->buttons[event->button] = 0;
	}
}
#endif
