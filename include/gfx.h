#ifndef GFX_H
#define GFX_H

#include <nds.h>

/* draw */
void gfx_draw_px(int x, int y, u16 col);
void gfx_draw_line(int x0,int y0,int x1,int y1,u16 c);
void gfx_draw_circle(int cx, int cy, int r, u16 col);

#endif /* GFX_H */

