
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities
#include "striped_circle.h"

int main() {
    
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    Striped_circle b{Point{300, 200}, 100};
    b.set_color(Color::blue);
    b.set_fill_color(Color::yellow);
    win.attach(b);

    win.wait_for_button();       // give control to the display engine
    
}