#ifndef STRIPED_CIRCLE_H_
#define STRIPED_CIRCLE_H_

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "../../../GUI/Point.h"
#include "../../../GUI/Graph.h"
#include "../../../GUI/Window.h"
#include "../../../std_lib_facilities.h"

namespace Graph_lib {
    class Striped_circle : public Circle {
	public:
		Striped_circle(Point p, int rr) : Circle(p, rr) {
	}

	void draw_lines() const;
private:
};

}

#endif