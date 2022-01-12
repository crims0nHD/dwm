#ifndef _BARS_H_
#define _BARS_H_

#include "preconfig.h"

enum {BarPosTop, BarPosRight, BarPosBottom, BarPosLeft}; /* Bar positions */
enum {
	BarAppletTags,
	BarAppletWindowLayout,
	BarAppletWindows,
	BarAppletClock,
	BarAppletDWMVersionNumber,
};

typedef struct BarApplet {
	union {
		struct BarApplet** group;
		unsigned int group_c;
		unsigned int applet;
	};
	unsigned int isGroup;
	unsigned int padding_inner;
	unsigned int padding_start;
	unsigned int padding_end;
	unsigned int option; /* Type dependent */
} BarApplet;

typedef struct {
	unsigned int position;
	BarApplet *applet_s;	
	BarApplet *applet_e;	
	int *monitors;
} Bar;

void mon_draw_bars(Monitor *m, Bar **bs, unsigned int b_count);

#endif /* _BARS_H_ */
