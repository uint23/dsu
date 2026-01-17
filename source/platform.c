#include <nds.h>

#include "config.h"
#include "platform.h"

int bg_sub;

void platform_init(void)
{
	if (g_config.bottom_display) {
		lcdMainOnBottom();
		videoSetMode(MODE_FB0);
		vramSetBankA(VRAM_A_LCD);
		videoSetModeSub(MODE_5_2D);
		vramSetBankC(VRAM_C_SUB_BG);
		bg_sub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	}
	else {
		lcdMainOnTop();
		videoSetMode(MODE_FB0);
		vramSetBankA(VRAM_A_LCD);
		videoSetModeSub(MODE_5_2D);
		vramSetBankC(VRAM_C_SUB_BG);
		bg_sub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	}
	irqEnable(IRQ_VBLANK);
}

