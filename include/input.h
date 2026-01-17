#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include <nds.h>

struct input {
	/* stylus */
	int           x;
	int           y;

	bool          sty_held;
	bool          sty_pressed;
	bool          sty_released;

	/* buttons */
	u32           btn_held;
	u32           btn_down;
	u32           btn_up;
};

extern struct input in;

void input_poll(void);

#endif /* INPUT_H */

