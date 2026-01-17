/*  dsu! -- osu! for the ds
	
	dsu! is licensed under a
	source-open licence.

	check LICENSE for more
	info
*/

#include <stdlib.h>

#include <nds.h>

#include "clock.h"
#include "input.h"
#include "platform.h"
#include "scene.h"

#include "scenes/scene_play.h"

/* globals */
struct input in;

void run(void)
{
	while (pmMainLoop()) {
		swiWaitForVBlank();
		clock_tick();
		input_poll();
		scene_update();
		scene_render();
	}
}

void setup(void)
{
	platform_init();
	scene_set(&scene_play);
}

int main(void)
{
	setup();
	run();

	return EXIT_SUCCESS;
}

