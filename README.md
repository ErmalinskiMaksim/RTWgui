# Reinvent-The-Wheel gui (RTWgui)
## 1. Description
This is small GUI framework that automates the run-of-the-mill GUI boilerplate like:
1. C++ GUI library APIs (SFML and SDL3+SDL3_TTF) at the moment
2. Layer logic (creation of layers, intercommunication, etc.)
3. Some basic widgets (menus, dialogs, pop-ups, taskbars, toolbars)
4. Event handling

## 2. What does it require?
The main requirement is having two variables in the root CMakeLists:\
```Root Project Directory:```\
```|_ YourApp/```\
```    |_...```
```|_ ...```\
```|_CMakeLists.txt # <- this one```\
It requires *GUI_ENABLE_LTO* and *GRAPHICS_LIBRARY* (either **SDL** or **SFML**).\
Example:\

```CMake 
# LTO
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)
if (IPO_SUPPORTED)
    set(GUI_ENABLE_LTO ON)
else()
    set(GUI_ENABLE_LTO OFF)
endif()

# GUI LIB OPTION
set(GRAPHICS_LIBRARY "SDL" CACHE STRING "Graphics backend: SDL or SFML")
set_property(CACHE GRAPHICS_LIBRARY PROPERTY STRINGS SDL SFML)
```
## 3. Composition
The framework contains several major modules:
1. Widgets in *Widgets/*
2. Interactors in *Interactors/*
3. Some must have entities like Window, Renderer, Font, Main GUI supervisor, and redefinitions of external library types (SFML or SDL3)
4. The other important components like Events, Requests, Responses, Layers
## 4. How to use it?
In your main() just write:
```cpp 
#include "RTWgui/RTWgui.h"

int main() {
    try {
        RTWgui::run();
    } catch(...) {

    }
}
```
\
To customize the GUI layout, you will *MUST* create an init.cpp file:
```cpp 
#include "Init.h"

// Custom handler includes for layers

// Custom Interactor includes

// Mandatory parameters 
// Window
const std::string_view WINDOW_TITLE = ...;
const unsigned WINDOW_WIDTH  = ...;
const unsigned WINDOW_HEIGHT = ...;

// Font
const std::string_view MAIN_FONT_PATH = ...;
const float MAIN_FONT_SZ = ...;

const size_t MAIN_LAYER_COUNT = ...; // must be > 0

void initializeLayers(LayerArray& layers, float mainFontCharWidth, float mainFontCharHeight) {
    // initialize your layers here
}
```
***How to initialize layers***?\
```cpp 
 // task bar + tool bar example
    layers[0] = std::make_unique
        <Layer<Widget, ToolBarInteractor, NonModalLayerCreateRequest
        , .../*YOUR CUSTOM HANDLERS*/...>>(
            NonModalLayerCreateRequest{
                Widget {
                    Rect{0.0f, 0.05f * WINDOW_HEIGHT, WINDOW_WIDTH, 0.15f * WINDOW_HEIGHT}
                    , Color{0xBB, 0xBB, 0xBB, 0xFF}
                    , Color{0xBB, 0xBB, 0xBB, 0xFF}
                    , mainFontCharWidth
                    , mainFontCharHeight
                }, NonModalLayerCreateRequest::Payload{}}); 
            , /* YourCustomHandler1{}*/
            , /* YourCustomHandler2{}*/
            , /*... YourCustomHandlerN{}*/);
    layers[1] = std::make_unique
        <Layer<Widget, TaskBarInteractor, NonModalLayerCreateRequest
        , .../*YOUR CUSTOM HANDLERS*/...>>(
            NonModalLayerCreateRequest{
                Widget {
                    Rect{0.0f, 0.0f, WINDOW_WIDTH, 0.05f * WINDOW_HEIGHT}
                    , Color{0xCC, 0xCC, 0xCC, 0xFF}
                    , Color{0xCC, 0xCC, 0xCC, 0xFF}
                    , mainFontCharWidth
                    , mainFontCharHeight
                }, NonModalLayerCreateRequest::Payload{}}
            , /* YourCustomHandler1{}*/
            , /* YourCustomHandler2{}*/
            , /*... YourCustomHandlerN{}*/);

```
### Break down of components
In the previous example, you could observe the creation of a tool bar and a task bar layers. They needed the following components:
1. Widget (either from the framework or user-defined)
2. Interactor (either from framework or user-defined)
3. Request which creates it (for non-modal layers, it's always the same and comes out-of-the-box)
4. Handlers (user-defined only)
### What are those entities?
1. Widget = an immutable graphical object that defines how to draw itself
2. Interactor = an entity that manages the logic of the layer. It's bound to the layer's main widget
3. Handler = a request/response handler of a layer. Example: a handler of one of the task bar's buttons 1) defines its menu (amount of options, menu widget, and actions tied to each option); 2) catches a response from the menu layer, and 3) performs a corresponding action. Sometimes, the handlers must perform the operation not just on some global value but on the interactor that called it. There is a special API in the Interactor class for this case.

### User defined components 
1. Widgets: to make a custom widget, derive it from RTWgui's Widget
2. Interactors: for the reference, look at *headers/Layer.h* and *Interactors/* directory. In a nutshell, a custom Interactor must have: 
```cpp
template<WidgetType MainWidget, ResponseHandler... Handlers>
class CustomInteractor{
public:
    void dispatchEvents(const LayerEvent& event);
    void render(const Renderer& renderer, const Font& font) const;
    static constexpr bool hasOperations;

    // for non-modal layers whose hasOperation = true
    // Example, when it's useful:
    // A spreadsheets interctor. When the user clicks on the label space, a menu appears with "insert/delete column/row". The result of this operation must be returned back to the caller and be concumed by some global entity
    OperationView getOperation();
    void processOperation();
private:
    WidgetView r_widget;
    RequestView r_pendingRequest;
    // when hasOperation = true;
    OperationRegister CustomInteractor::m_operation;
};
```  
3. Handlers 
You can inspect the *headers/Handlers.h* file, there is a corresponding concept that outlines the requirements.
## 5. Project examples
See a [spreadsheets](https://github.com/ErmalinskiMaksim/Spreadsheets-plus-plus) application powered by this framework.
