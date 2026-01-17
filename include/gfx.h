#ifndef GFX_H
#define GFX_H

#include <stdbool.h>

#include <nds.h>

void gfx_clear(u16 col);
void gfx_load_sub(const void* data, int len);

/* draw */
void gfx_draw_px(int x, int y, u16 col);
void gfx_draw_line(int x0,int y0,int x1,int y1,u16 c);
void gfx_draw_circle(int cx, int cy, int r, u16 col, bool fill);
void gfx_draw_sprite(int x, int y, int w, int h, const void* data);

#endif /* GFX_H */

