#include <nds.h>

#include "config.h"

struct config g_config;

void config_init(void)
{
	g_config.bottom_display = true;
	g_config.touch_press  = true;
	g_config.hit_buttons  = KEY_A | KEY_B | KEY_X | KEY_Y |
                            KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT;
}
