#include <math.h>
#include <stdlib.h>

#include <nds.h>

#include "gfx.h"
#include "input.h"
#include "platform.h"

void run(void);
void setup(void);

void run(void)
{
	float a = 0.0f;

	u8 x = 0;
	u8 r = 0;
	u8 g = 0;
	u8 b = 0;

	for (;;) {
		swiWaitForVBlank();
		dmaFillHalfWords(0, VRAM_A, SCRW * SCRH * 2);

		gfx_draw_circle(SCRW/2, SCRH/2, x, RGB15(r, g, b));
		gfx_draw_circle(SCRW/4, SCRH/3, x, RGB15(r, g, b));
		gfx_draw_circle(SCRW/3, SCRH/4, x, RGB15(r, g, b));
		if (x >= 192/2)
			x = 0;
		x++; r+=1; g+=2; b+=3;

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

