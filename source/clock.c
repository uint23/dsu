#include "clock.h"

u32 g_frame;

void clock_tick(void)
{
	g_frame++;
}

