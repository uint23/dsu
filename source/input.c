#include <stdbool.h>

#include <nds.h>

#include "input.h"

void input_poll(void)
{
	static bool prev_touch = 0;

	scanKeys();
	touchPosition t;
	touchRead(&t);

	bool touch_now = (keysHeld() & KEY_TOUCH) ? true : false;

	in.x = t.px;
	in.y = t.py;

	in.sty_held = touch_now;
	in.sty_pressed = (touch_now && !prev_touch);
	in.sty_released = (!touch_now && prev_touch);

	in.btn_held = keysHeld();
	in.btn_down = keysDown();
	in.btn_up = keysUp();

	prev_touch = touch_now;
}

