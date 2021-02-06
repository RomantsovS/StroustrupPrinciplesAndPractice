#ifndef ARC_H_
#define ARC_H_

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "../../../GUI/Point.h"
#include "../../../GUI/Graph.h"
#include "../../../std_lib_facilities.h"

namespace Graph_lib {

    struct Arc : Shape {
	Arc(Point p, int ww, int hh, int aa1, int aa2)	// center, min, and max distance from center
		:w(ww), h(hh), a1(aa1), a2(aa2) { add(Point(p.x-ww,p.y-hh)); }

	void draw_lines() const;

	Point center() const { return Point(point(0).x+w,point(0).y+h); }
	Point focus1() const {
			if (h<=w)// foci are on the x-axis:
					return Point(center().x+int(sqrt(double(w*w-h*h))),center().y);
			else	// foci are on the y-axis:
					return Point(center().x,center().y+int(sqrt(double(h*h-w*w))));
	}

	Point focus2() const {
			if (h<=w)
					return Point(center().x-int(sqrt(double(w*w-h*h))),center().y);
			else
					return Point(center().x,center().y-int(sqrt(double(h*h-w*w))));
	}
	//Point focus2() const { return Point(center().x-int(sqrt(double(abs(w*w-h*h)))),center().y); }
	
	void set_major(int ww) { set_point(0,Point(center().x-ww,center().y-h)); w=ww; }
	int major() const { return w; }
	void set_minor(int hh) { set_point(0,Point(center().x-w,center().y-hh)); h=hh; }
	int minor() const { return h; }
private:
	int w;
	int h;
	int a1, a2;
};

}

#endif