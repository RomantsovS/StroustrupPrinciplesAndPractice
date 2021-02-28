
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities

double one(double) {return 1;}
double slope(double x) {return x / 2;}
double square(double x) {return x * x;}

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

    Function s{one, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2{slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s3{square, r_min, r_max, orig, n_points, x_scale, y_scale};

    win.attach(s);
    win.attach(s2);
    win.attach(s3);
    
    fl_font(fl_font(), 10);

    Text ts{Point{100, y_orig - 40}, "one"};
    Text ts2{Point{100, y_orig + y_orig / 2 - 20}, "x / 2"};
    Text ts3{Point{x_orig - 100, 20}, "x * x"};

    win.attach(ts);
    win.attach(ts2);
    win.attach(ts3);

    win.set_label("Function graphing: label functions");

    constexpr int xlength = xmax - 40;
    constexpr int ylength = ymax - 40;

    Axis x{Axis::x, Point{20, y_orig}, xlength, xlength / x_scale, "one notch == 1"};
    Axis y{Axis::y, Point{x_orig, ylength + 20}, ylength, ylength / x_scale, "one notch == 1"};

    x.set_color(Color::red);
    y.set_color(Color::red);

    Function s5{[](double x) {return cos(x) + slope(x);},
    r_min, r_max, orig, 400, 30, 30};

    win.attach(s5);

    win.attach(x);
    win.attach(y);

    win.wait_for_button();       // give control to the display engine
    
}