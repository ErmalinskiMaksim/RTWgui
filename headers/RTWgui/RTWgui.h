#ifndef RTW_GUI_H 
#define RTW_GUI_H

#include "RTWgui/LibraryDependent/GUI.h"

// Main class
class RTWgui {
public:
    // main loop 
    static void run() {
        if (!GUI::init()) throw; 
        while(processEvents()) display();
    }
private:
    // currently supports only gui mode
    static bool processEvents() {
        return GUI::get().processEvents();
    }

    static void update() {
        return GUI::get().update();
    }

    static void display() {
        GUI::get().draw();
    }
};

#endif // 
