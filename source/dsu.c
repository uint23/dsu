#include <math.h>
#include <stdlib.h>

#include <nds.h>

#include "platform.h"

int main(void)
{
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);

	for (;;)
		;
}
