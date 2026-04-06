#ifndef GUI_H
#define GUI_H

#include "RTWgui/LibraryDependent/LibraryLifetime.h"
#include "RTWgui/LibraryDependent/Renderer.h"
#include "RTWgui/LayerFocusStack.h"
#include <memory>


// The main GUI manager class 
// * initializes and destroys libraries 
// * owns windows, renderers, fonts and graphical layers
// * dispatches events to layers in a centralized maner 
// * allows for communication between layers via requests&responses
// * deals with layer stack and determines focus
class GUI {
public:
    // singleton
    GUI(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI& operator=(GUI&&) = delete;
    ~GUI();

    static GUI& get() {
        static GUI gui;
        return gui;
    }
    
    // process application events and dispatch them to layers 
    bool processEvents();
    // updates application layers 
    void update();
    // let all the layers draw themselves
    void draw() const;
private:
    GUI();
   
    // process layer requests
    bool processRequests();
    
    // z-depth array of layers [bottom->top]
    LayerOwningArray m_layers; 
    // non owning focus stack of layers
    LayerFocusStack m_focusStack;
    // library lifetime controller
    LibraryLifetime m_libLT;
    // main renderer
    Renderer m_renderer;
    // main font
    Font m_mainFont;
};

#endif // !GUI_H
