#include "box.h"

namespace Graph_lib {

void Box::draw_lines() const
{
   if (fill_color().visibility()) {    // fill
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x,point(0).y,w,h);
        fl_color(color().as_int());    // reset color
    }

    if (color().visibility()) {    // lines on top of fill
        fl_color(color().as_int());
        fl_rect(point(0).x,point(0).y,w,h);
    }

	arcs[0].draw_lines();
}

void Box::attach_arcs(Window& win) {
	win.attach(arcs[0]);
}

}