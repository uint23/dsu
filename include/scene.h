#ifndef SCENE_H
#define SCENE_H

struct scene {
	void          (*enter)(void);
	void          (*leave)(void);
	void          (*update)(void);
	void          (*render)(void);
};

void scene_render(void);
void scene_set(struct scene* s);
void scene_update(void);

#endif /* SCENE_H */

