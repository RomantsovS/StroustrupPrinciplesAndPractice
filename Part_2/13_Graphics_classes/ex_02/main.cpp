
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities
#include "arc.h"
#include "box.h"

int main() {
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    std::cout << tl.x << std::endl;

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    Box b{Point{200, 20}, 150, 250, 50};
    win.attach(b);

    win.wait_for_button();       // give control to the display engine
    
}