#include <math.h>
#include <stdlib.h>

#include <nds.h>

#include "gfx.h"
#include "input.h"
#include "platform.h"

void run(void);
void setup(void);

struct input inp;

void run(void)
{
	float a = 0.0f;


	struct {
		u8 x;
		u8 r;
		u8 g;
		u8 b;
	}* circles = NULL;
	int ncirc = 0;

	for (;;) {
		swiWaitForVBlank();
		dmaFillHalfWords(0, VRAM_A, SCRW * SCRH * 2);
		input_poll(&inp);

		if (inp.sty_held)
			gfx_draw_line(SCRW/2, SCRH/2, inp.x, inp.y, RGB8(255, 255, 255));

		if (inp.btn_down & KEY_A) {
			ncirc++;
			circles = realloc(circles, ncirc * sizeof(*circles));
			circles[ncirc - 1].x = 0;
			circles[ncirc - 1].r = rand() % 32;
			circles[ncirc - 1].g = rand() % 32;
			circles[ncirc - 1].b = rand() % 32;
		}

		for (size_t i = 0; i < ncirc; i++) {
			gfx_draw_circle(SCRW/2, SCRH/2, circles[i].x, RGB15(circles[i].r, circles[i].g, circles[i].b));
			gfx_draw_circle(SCRW/2, SCRH/2, circles[i].x+1, RGB15(circles[i].r, circles[i].g, circles[i].b));
			gfx_draw_circle(SCRW/2, SCRH/2, circles[i].x+2, RGB15(circles[i].r, circles[i].g, circles[i].b));
			circles[i].x++;
			circles[i].r += 1;
			circles[i].g += 2;
			circles[i].b += 3;

			if (circles[i].x == 0) {
				circles[i] = circles[ncirc - 1];
				ncirc--;
				circles = realloc(circles, ncirc * sizeof(*circles));
				i--;
			}
		}

		a += 0.05f;
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

