#include "striped_rectangle.h"

namespace Graph_lib
{

	void Striped_rectangle::draw_lines() const
	{
		if (fill_color().visibility()) // fill
		{
			fl_color(fill_color().as_int());
			fl_line_style(0, 3);

			for(int i = 10; i < height(); i += 10) {
				fl_line(point(0).x, point(0).y + i,
				point(0).x + width(), point(0).y + i);
			}

			fl_color(color().as_int()); // reset color
		}

		fl_line_style(0, 1);

		if (color().visibility()) // lines on top of fill
		{ 
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, width(), height());
		}
	}

} // namespace Graph_lib