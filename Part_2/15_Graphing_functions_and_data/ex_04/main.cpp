
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities

int main() {
    
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    constexpr int xmax = 600;
    constexpr int ymax = 400;

    constexpr int x_orig = xmax / 2;
    constexpr int y_orig = ymax / 2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;
    constexpr int r_max = 11;

    constexpr int n_points = 400;
    constexpr int x_scale = 30;
    constexpr int y_scale = 30;

    Simple_window win{Point{100, 100}, xmax, ymax, "Function graphing"};
    
    fl_font(fl_font(), 10);

    win.set_label("Function graphing: label functions");

    constexpr int xlength = xmax - 40;
    constexpr int ylength = ymax - 40;

    Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale, "one notch == 1"};
    Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / y_scale, "one notch == 1"};

    x.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    Function s1{[](double x) {return cos(x);},
    r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s1);

    Function s2{[](double x) {return sin(x);},
    r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s2);

    Function s3{[](double x) {return sin(x) + cos(x);},
    r_min, r_max, orig, n_points, x_scale, y_scale};
    s3.set_color(Color::yellow);
    win.attach(s3);

    Function s4{[](double x) {return sin(x) * sin(x) + cos(x) * cos(x);},
    r_min, r_max, orig, n_points, x_scale, y_scale};
    s4.set_color(Color::red);
    win.attach(s4);

    win.wait_for_button();       // give control to the display engine
    
}