
#include "../../../GUI/Simple_window.h"    // get access to our window library
#include "../../../GUI/Graph.h"            // get access to our graphics library facilities

int main() {
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    std::cout << tl.x << std::endl;

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    Vector_ref<Rectangle> vr;

    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            vr.push_back(new Rectangle{Point{i * 20, j * 20}, 20, 20});
            vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
            win.attach(vr[vr.size() - 1]);
        }
    }

    win.wait_for_button();       // give control to the display engine
    
}