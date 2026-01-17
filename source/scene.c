#include "scene.h"

static struct scene* cur;

void scene_render(void)
{
	if (cur && cur->render)
		cur->render();
}

void scene_set(struct scene* s)
{
	if (cur && cur->leave)
		cur->leave();

	cur = s;
	if (cur && cur->enter)
		cur->enter();
}

void scene_update(void)
{
	if (cur && cur->update)
		cur->update();
}

