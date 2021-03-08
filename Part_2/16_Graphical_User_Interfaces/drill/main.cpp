//
// This is example code from Chapter 16.5 "An example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>
#include <sstream>
#include "../../../GUI/Graph.h"         // get access to our graphics library facilities
#include "../../../GUI/GUI.h"
#include "../../../GUI/Window.h"

using namespace Graph_lib;
using namespace std;

//------------------------------------------------------------------------------

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title );
private:
    // Data:
    Open_polyline lines;

    // Widgets:
    Button next_button;    // add (next_x,next_y) to lines
    Button quit_button;    // end program
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    Menu color_menu, line_style_menu;
    Button color_menu_button, line_style_menu_button;

    void change(Color c) { lines.set_color(c); }
    void change_style(Line_style ls) { lines.set_style(ls); }

    void hide_menu_color() { color_menu.hide(); color_menu_button.show(); } 
    void hide_menu_line_style() { line_style_menu.hide(); line_style_menu_button.show(); } 

    // actions invoked by callbacks:
    void red_pressed() { change(Color::red); hide_menu_color(); }
    void blue_pressed() { change(Color::blue); hide_menu_color(); } 
    void yellow_pressed() { change(Color::yellow); hide_menu_color(); } 
    void color_menu_pressed() { color_menu_button.hide(); color_menu.show(); }
    void line_style_menu_pressed() { line_style_menu_button.hide(); line_style_menu.show(); }
    void next();
    void quit();

    void dash_pressed() { change_style(Line_style::dash); hide_menu_line_style(); }
    void dashdot_pressed() { change_style(Line_style::dot); hide_menu_line_style(); }

    // callback functions:
    static void cb_red(Address, Address);
    static void cb_blue(Address, Address);
    static void cb_yellow(Address, Address); 
    static void cb_menu_color(Address, Address);
    static void cb_menu_line_style(Address, Address);
    static void cb_next(Address, Address);
    static void cb_quit(Address, Address);
};

//------------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
    next_button(Point(x_max()-150,0), 70, 20, "Next point", cb_next),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
    next_x(Point(x_max()-310,0), 50, 20, "next x:"),
    next_y(Point(x_max()-210,0), 50, 20, "next y:"),
    xy_out(Point(100,0), 100, 20, "current (x,y):"),
    color_menu(Point(x_max()-70,30),70,20,Menu::vertical,"color"),
    line_style_menu(Point(x_max()-170,30),70,20,Menu::vertical,"line_style"),
    color_menu_button(Point(x_max()-80,30), 80, 20, "color menu", cb_menu_color),
    line_style_menu_button(Point(x_max()-220,30), 120, 20, "line style menu", cb_menu_line_style)
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button(Point(0,0),0,0,"red",cb_red));
    color_menu.attach(new Button(Point(0,0),0,0,"blue",cb_blue));
    color_menu.attach(new Button(Point(0,0),0,0,"yellow",cb_yellow));
    attach(color_menu);
    color_menu.hide();
    attach(color_menu_button);
    attach(lines);
    
    line_style_menu.attach(new Button(Point(0,0),0,0,"dash",
        [](Address, Address pw) {reference_to<Lines_window>(pw).dash_pressed();}));
    line_style_menu.attach(new Button(Point(0,0),0,0,"dashdot",
        [](Address, Address pw) {reference_to<Lines_window>(pw).dashdot_pressed();}));
    attach(line_style_menu);
    line_style_menu.hide();
    attach(line_style_menu_button);
}

//------------------------------------------------------------------------------

void Lines_window::cb_quit(Address, Address pw)    // "the usual"
{  
       reference_to<Lines_window>(pw).quit();
} 

//------------------------------------------------------------------------------

void Lines_window::quit()
{
    hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------

void Lines_window::cb_next(Address, Address pw)     // "the usual"
{  
       reference_to<Lines_window>(pw).next();
} 

//------------------------------------------------------------------------------

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point(x,y));

    // update current position readout:
    stringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

      redraw();
}

//------------------------------------------------------------------------------

void Lines_window::cb_red(Address, Address pw)      // "the usual"
{  
    reference_to<Lines_window>(pw).red_pressed();
} 

//------------------------------------------------------------------------------

void Lines_window::cb_blue(Address, Address pw)     // "the usual"
{  
    reference_to<Lines_window>(pw).blue_pressed();
} 

//------------------------------------------------------------------------------

void Lines_window::cb_yellow(Address, Address pw)    // "the usual"
{  
    reference_to<Lines_window>(pw).yellow_pressed();
} 

//------------------------------------------------------------------------------

void Lines_window::cb_menu_color(Address, Address pw)     // "the usual"
{  
    reference_to<Lines_window>(pw).color_menu_pressed();
}

void Lines_window::cb_menu_line_style(Address, Address pw)     // "the usual"
{  
    reference_to<Lines_window>(pw).line_style_menu_pressed();
}

//------------------------------------------------------------------------------

int main()
try {
    Lines_window win(Point(100,100),600,400,"lines");
    return gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}

//------------------------------------------------------------------------------