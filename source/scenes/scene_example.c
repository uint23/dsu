#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "scene.h"
#include "scenes/scene_example.h"

static void enter(void);
static void update(void);
static void render(void);

static int inside(int x, int y, int cx, int cy, int r);

static int cx;
static int cy;
static int r;
static int hit_flash;

static int curx;
static int cury;

static void enter(void)
{
	cx = SCRW/2;
	cy = SCRH/2;
	r = 24;
	hit_flash = 0;
}

static void update(void)
{
	if ((in.btn_down & KEY_UP) && inside(in.x, in.y, cx, cy, r))
		hit_flash = 8;

	if (hit_flash > 0)
		hit_flash--;

	curx = in.x;
	cury = in.y;
}

static void render(void)
{
	gfx_clear(RGB15(0,0,0));

	u16 col = (hit_flash > 0) ? RGB15(0,31,0) : RGB15(31,31,31);
	gfx_draw_circle(cx, cy, r, col);

	/* stylus cursor */
	gfx_draw_circle(curx, cury, 3, RGB8(100, 100, 100));
}

static int inside(int x, int y, int cx, int cy, int r)
{
    int dx = x - cx;
    int dy = y - cy;
    return (dx*dx + dy*dy) <= r*r;
}

struct scene scene_example = {
	.enter = enter,
	.leave = NULL,
	.render = render,
	.update = update,
};

