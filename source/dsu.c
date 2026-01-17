/*  dsu! -- osu! for the ds
	
	dsu! is licensed under a
	source-open licence.

	check LICENSE for more
	info
*/

#include <math.h>
#include <stdlib.h>

#include <nds.h>

#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "scene.h"

/* scenes */
#include "scenes/scene_example.h"

/* prototypes */
void run(void);
void setup(void);

/* variables */
struct input in;

/* functions */
void run(void)
{
	scene_set(&scene_example);
	for (;;) {
		swiWaitForVBlank();

		input_poll();

		scene_update();
		scene_render();
	}
}

void setup(void)
{
	/* platform */
	platform_init();
}

int main(void)
{
	setup();
	run();

	return EXIT_SUCCESS;
}

