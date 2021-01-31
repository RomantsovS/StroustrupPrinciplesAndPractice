
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities

//------------------------------------------------------------------------------

int main() {
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    std::cout << tl.x << std::endl;

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    Polygon poly;                // make a shape (a polygon)

    poly.add(Point(300,200));    // add a point
    poly.add(Point(350,100));    // add another point
    poly.add(Point(400,200));    // add a third point 

    poly.set_color(Color::red);  // adjust properties of poly
    poly.set_style(Line_style(Line_style::dash, 4));
    win.attach (poly);           // connect poly to the window

    Axis xa{Axis::x, Point{20, 300}, 280, 10, "x axis"};
    win.attach(xa);
    Axis ya{Axis::y, Point{20, 300}, 280, 10, "y axis"};
    ya.set_color(Color::red);
    win.attach(ya);

    Function sine{sin, 0, 100, Point{20, 150}, 1000, 50, 50};
    win.attach(sine);

    Rectangle r{Point{200, 200}, 100, 50};
    r.set_fill_color(Color::yellow);
    win.attach(r);

    Text t{Point{150, 150}, "Hello"};
    win.attach(t);

    Image ii{Point{10, 10}, "image.jpg"};
    win.attach(ii);

    win.wait_for_button();       // give control to the display engine

}

//------------------------------------------------------------------------------