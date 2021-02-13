#ifndef STRIPED_RECTANGLE_H_
#define STRIPED_RECTANGLE_H_

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "../../../GUI/Point.h"
#include "../../../GUI/Graph.h"
#include "../../../GUI/Window.h"
#include "../../../std_lib_facilities.h"

namespace Graph_lib {
    class Striped_rectangle : public Rectangle {
	public:
		Striped_rectangle(Point p, int ww, int hh) : Rectangle(p, ww, hh) {
	}

	void draw_lines() const;
private:
};

}

#endif