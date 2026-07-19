#ifndef INPUT_H
#define INPUT_H


#define MAX_KEYBOARD_KEYS 232
// #define MAX_CBUF_KEYBOARD_KEYS 4
#define MAX_MOUSE_BUTTONS 4

/* ---------------------------------------------------------------------------------------------------- */

#if 0
struct cbuf_keyboard
{
	int keys[MAX_CBUF_KEYBOARD_KEYS];
};
#endif

struct keyboard
{
	int keys[MAX_KEYBOARD_KEYS];
	// struct cbuf_keyboard cbuf;
};

#if 0
struct mouse
{
	int x;
	int y;

	int buttons[MAX_MOUSE_BUTTONS];
};
#endif

struct events
{
	struct keyboard keyboard;
	// struct mouse mouse;
};

/* ---------------------------------------------------------------------------------------------------- */

void input(struct events *events);


#endif // INPUT_H
