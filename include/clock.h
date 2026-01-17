#ifndef CLOCK_H
#define CLOCK_H

#include <nds.h>

extern u32 g_frame;

void clock_tick(void);

static inline uint32_t clock_ms(void) { return g_frame * 1000 / 60; }

#endif /* CLOCK_H */

