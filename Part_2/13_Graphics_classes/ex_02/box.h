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
		
		l.add(Point{p.x + rr, p.y}, Point{p.x + ww - rr, p.y});
		l.add(Point{p.x + rr, p.y + hh}, Point{p.x + ww - rr, p.y + hh});

		l.add(Point{p.x, p.y + rr}, Point{p.x, p.y + hh - rr});
		l.add(Point{p.x + ww, p.y + rr}, Point{p.x + ww, p.y + hh - rr});

		arcs[0] = Arc{Point{p.x + rr, p.y + rr}, rr, rr, 90, 180};
		arcs[1] = Arc{Point{p.x + ww - rr, p.y + rr}, rr, rr, 0, 90};
		arcs[2] = Arc{Point{p.x + rr, p.y + hh - rr}, rr, rr, 180, 270};
		arcs[3] = Arc{Point{p.x + ww - rr, p.y + hh - rr}, rr, rr, 270, 360};
	}

	void draw_lines() const;
	void attach_arcs(Window& win);
private:
	int w;
	int h;
	int radius;
	Arc arcs[4];
	Lines l;
};

}

#endif