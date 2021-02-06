
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities
#include "arc.h"

int main() {
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    std::cout << tl.x << std::endl;

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    Ellipse e1{Point{320, 120}, 100, 50};

    win.attach(e1);

    Arc arc1{Point{200, 200}, 50, 50, 180, 270};
    //arc1.set_fill_color(Color::blue);
    win.attach(arc1);

    win.wait_for_button();       // give control to the display engine
    
}