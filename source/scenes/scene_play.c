#include <stdlib.h>

#include <nds.h>

#include "clock.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "scene.h"
#include "scenes/scene_play.h"

#include "bottom_grid.h"
#include "circle.h"

#define PREEMPT_MS 800
#define HIT_300_MS 40
#define HIT_100_MS 80
#define HIT_50_MS  120

struct hitobj {
	int            x;
	int            y;
	u32            t_ms;   /* hit time */
	int            hit;    /* 0=none, 1=hit, -1=miss */
};

static struct hitobj map[] = {
	{  80,  60, 1000, 0 },
	{ 180,  80, 1500, 0 },
	{ 120, 140, 2000, 0 },
	{  70, 120, 2500, 0 },
	{ 200, 130, 3000, 0 },
};

static int cur_idx;
static int flash;
static int last_judge;
static u32 loop_offset;

#define FLASH_MAX    128
#define FLASH_OUT    8    /* fade out speed */
#define GLOW_DEPTH   8    /* pixels of inner glow */

#define MAP_LEN      (sizeof(map)/sizeof(map[0]))
#define LOOP_MS      3500 /* 3.5s */

static int inside(int x, int y, int cx, int cy, int r)
{
	int dx = x - cx;
	int dy = y - cy;
	return (dx*dx + dy*dy) <= r*r;
}

static int judge_delta(u32 d)
{
	if (d <= HIT_300_MS)
		return 300;
	else if (d <= HIT_100_MS)
		return 100;
	else if (d <= HIT_50_MS)
		return 50;

	return 0;
}

static void reset_map(void)
{
	cur_idx = 0;
	for (size_t i = 0; i < MAP_LEN; i++)
		map[i].hit = 0;
}

static void enter(void)
{
	gfx_load_sub(bottom_gridBitmap, bottom_gridBitmapLen);
	flash = 0;
	last_judge = 0;
	loop_offset = 0;
	reset_map();
}

static void update(void)
{
	u32 raw_now = clock_ms();
	u32 now = raw_now - loop_offset;

	/* decay flash */
	if (flash > 0) {
		flash -= FLASH_OUT;
		if (flash < 0)
			flash = 0;
	}

	/* check if we should loop */
	if (cur_idx >= (int)MAP_LEN && now > map[MAP_LEN-1].t_ms + 500) {
		loop_offset = raw_now;
		reset_map();
		return;
	}

	/* advance past missed objects */
	for (;;) {
		if (cur_idx >= (int)MAP_LEN)
			break;

		struct hitobj* o = &map[cur_idx];

		if (o->hit != 0) {
			cur_idx++;
			continue;
		}

		/* miss if too late */
		if (now > (o->t_ms + HIT_50_MS)) {
			o->hit = -1;
			last_judge = 0;
			flash = FLASH_MAX;
			cur_idx++;;
			continue;
		}
		break;
	}

	/* hit with A, B press */
	if ((in.btn_down & (KEY_A | KEY_B)) && cur_idx < (int)MAP_LEN) {
		struct hitobj* o = &map[cur_idx];

		u32 dt = (now > o->t_ms) ? (now - o->t_ms) : (o->t_ms - now);
		int j = judge_delta(dt);

		if (j && inside(in.x, in.y, o->x, o->y, 15)) {
			o->hit = 1;
			last_judge = j;
			flash = FLASH_MAX;
			cur_idx++;
		}
	}
}

static void render_obj(const struct hitobj* o, u32 now)
{
	int r = 15; /* half of 30x30 sprite */

	/* spawn window */
	if (now + PREEMPT_MS < o->t_ms)
		return;
	if (now > o->t_ms + HIT_50_MS)
		return;
	if (o->hit != 0)
		return;

	/* approach circle */
	u32 start = o->t_ms - PREEMPT_MS;
	u32 span = PREEMPT_MS;
	u32 t = (now <= start) ? 0 : (now - start);
	if (t > span)
		t = span;

	int ar = r + (int)((2 * r) * (int)(span - t) / (int)span);
	gfx_draw_circle(o->x, o->y, ar, RGB15(10,10,10), false);

	/* draw circle sprite centered on hit position */
	gfx_draw_sprite(o->x - 15, o->y - 15, 30, 30, circleBitmap);
}

static void render(void)
{
	u32 now = clock_ms() - loop_offset;

	gfx_clear(RGB15(0,0,0));

	/* upcoming objects */
	for (size_t i = 0; i < MAP_LEN; i++)
		render_obj(&map[i], now);

	/* cursor */
	gfx_draw_circle(in.x, in.y, 10, RGB15(31, 31, 31), true);

	/* inner-glow flash */
	if (flash > 0) {
		int r = (last_judge == 300) ? 0  : (last_judge == 100) ? 31 : (last_judge == 50) ? 31 : 31;
		int g = (last_judge == 300) ? 31 : (last_judge == 100) ? 31 : (last_judge == 50) ? 15 : 0;
		int b = 0;

		for (int d = 0; d < GLOW_DEPTH; d++) {
			int alpha = (GLOW_DEPTH - d) * flash / (GLOW_DEPTH * FLASH_MAX / 31);
			if (alpha > 31)
				alpha = 31;
			if (alpha <= 0)
				continue;

			int pr = r * alpha / 31;
			int pg = g * alpha / 31;
			int pb = b * alpha / 31;
			u16 c = RGB15(pr, pg, pb);

			/* top edge */
			gfx_draw_line(d, d, SCRW - 1 - d, d, c);
			/* bottom edge */
			gfx_draw_line(d, SCRH - 1 - d, SCRW - 1 - d, SCRH - 1 - d, c);
			/* left edge */
			gfx_draw_line(d, d, d, SCRH - 1 - d, c);
			/* right edge */
			gfx_draw_line(SCRW - 1 - d, d, SCRW - 1 - d, SCRH - 1 - d, c);
		}
	}
}

struct scene scene_play = {
	.enter = enter,
	.leave = NULL,
	.update = update,
	.render = render,
};

