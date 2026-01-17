#include "platform.h"

#include <nds.h>

void platform_init(void)
{
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
}

