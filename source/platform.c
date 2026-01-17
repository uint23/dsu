#include <nds.h>

#include "platform.h"

int bg_sub;

void platform_init(void)
{
	lcdMainOnTop();
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
	videoSetModeSub(MODE_5_2D);
	vramSetBankC(VRAM_C_SUB_BG);
	irqEnable(IRQ_VBLANK);
	bg_sub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
}

