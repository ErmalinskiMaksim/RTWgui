#ifndef RTW_GUI_H 
#define RTW_GUI_H

#include "RTWgui/GUI.h"

// Main class
// It exists separately from GUI to allow for alternative
// interfaces in the future (like CLI)
class RTWgui {
public:
    // main loop 
    static void run() {
        while(processEvents()) {
            update();
            display();
        }
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
