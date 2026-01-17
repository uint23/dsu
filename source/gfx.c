#include <stdbool.h>

#include <nds.h>

#include "gfx.h"
#include "platform.h"

void gfx_clear(u16 col)
{
	dmaFillHalfWords(col | BIT(15), VRAM_A, SCRW * SCRH * 2);
}

void gfx_load_sub(const void* data, int len)
{
	u16* dst = (u16*)bgGetGfxPtr(bg_sub);
	const u16* src = (const u16*)data;
	int n = len / 2;

	if (n > 256 * 192)
		n = 256 * 192;

	for (int i = 0; i < n; i++)
		dst[i] = src[i] | BIT(15);
}

void gfx_draw_px(int x, int y, u16 col)
{
	if ((unsigned)x < SCRW && (unsigned)y < SCRH)
		VRAM_A[y * SCRW + x] = col | BIT(15);
}

void gfx_draw_line(int x0, int y0, int x1, int y1, u16 c)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	for (;;) {
		gfx_draw_px(x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2*err;
		if (e2 >= dy) {
			err += dy;
			x0 += sx;
		}

		if (e2 <= dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void gfx_draw_circle(int cx, int cy, int r, u16 col, bool fill)
{
	int x = r;
	int y = 0;
	int err = 0;

	while (x >= y) {

		if (fill) {
			for (int i = cx - x; i <= cx + x; i++) {
				gfx_draw_px(i, cy + y, col);
				gfx_draw_px(i, cy - y, col);
			}

			for (int i = cx - y; i <= cx + y; i++) {
				gfx_draw_px(i, cy + x, col);
				gfx_draw_px(i, cy - x, col);
			}
		}
		else {
			gfx_draw_px(cx + x, cy + y, col);
			gfx_draw_px(cx + y, cy + x, col);
			gfx_draw_px(cx - y, cy + x, col);
			gfx_draw_px(cx - x, cy + y, col);
			gfx_draw_px(cx - x, cy - y, col);
			gfx_draw_px(cx - y, cy - x, col);
			gfx_draw_px(cx + y, cy - x, col);
			gfx_draw_px(cx + x, cy - y, col);
		}

		y++;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0) {
			x--;
			err += 1 - 2 * x;
		}
	}
}

void gfx_draw_sprite(int x, int y, int w, int h, const void* data)
{
	const u16* src = (const u16*)data;

	for (int py = 0; py < h; py++) {
		for (int px = 0; px < w; px++) {
			u16 col = src[py * w + px];
			/* skip transparent */
			if (col & BIT(15))
				gfx_draw_px(x + px, y + py, col);
		}
	}
}

