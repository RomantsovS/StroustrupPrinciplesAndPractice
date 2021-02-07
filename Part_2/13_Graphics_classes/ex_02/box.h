#ifndef BOX_H_
#define BOX_H_

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "../../../GUI/Point.h"
#include "../../../GUI/Graph.h"
#include "../../../GUI/Window.h"
#include "../../../std_lib_facilities.h"
#include "arc.h"

namespace Graph_lib {

    struct Box : Shape {
	Box(Point p, int ww, int hh, int rr)
		:w(ww), h(hh), radius(rr) {
		add(Point(p.x,p.y));

		arcs[0] = Arc{Point{p.x + rr / 2, p.y + rr / 2}, rr, rr, 90, 180};
	}

	void draw_lines() const;
	void attach_arcs(Window& win);
private:
	int w;
	int h;
	int radius;
	Arc arcs[4];
};

}

#endif