#include "arc.h"

namespace Graph_lib {

void Arc::draw_lines() const
{
   if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,w+w-1,h+h-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, w+w, h+h, a1, a2);
	}
}

}