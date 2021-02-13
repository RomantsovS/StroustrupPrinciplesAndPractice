#include "striped_circle.h"

namespace Graph_lib
{

	void Striped_circle::draw_lines() const
	{
		int r = radius();

		if (fill_color().visibility()) // fill
		{
			fl_color(fill_color().as_int());
			fl_line_style(0, 3);

			for(int i = 10; i < r * 2; i += 10) {
				int x = std::sqrt(r * r - pow(r - i, 2));
				
				fl_line(center().x - x, point(0).y + i,
				center().x + x, point(0).y + i);
			}

			fl_color(color().as_int()); // reset color
		}

		fl_line_style(0, 1);

		if (color().visibility()) // lines on top of fill
		{ 
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r * 2, r * 2, 0, 360);
		}
	}

} // namespace Graph_lib