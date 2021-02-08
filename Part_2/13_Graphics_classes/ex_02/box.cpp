#include "box.h"

namespace Graph_lib {

void Box::draw_lines() const
{
   l.draw_lines();

	for(size_t i = 0; i < 4; ++i)
        arcs[i].draw_lines();
}

void Box::attach_arcs(Window& win) {
	win.attach(arcs[0]);
}

}