#include <stdbool.h>

#include <nds.h>

#include "input.h"

void input_poll(struct input* i)
{
	static bool prev_touch = 0;

	scanKeys();
	touchPosition t;
	touchRead(&t);

	bool touch_now = (keysHeld() & KEY_TOUCH) ? true : false;

	i->x = t.px;
	i->y = t.py;

	i->sty_held = touch_now;
	i->sty_pressed = (touch_now && !prev_touch);
	i->sty_released = (!touch_now && prev_touch);

	i->btn_held = keysHeld();
	i->btn_down = keysDown();
	i->btn_up = keysUp();

	prev_touch = touch_now;
}

