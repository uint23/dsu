#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

struct config {
	bool        bottom_display;
	bool        touch_press;
	int         hit_buttons;
};

extern struct config g_config;

void config_init(void);

#endif /* CONFIG_H */
