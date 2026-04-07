#ifndef INIT_H
#define INIT_H 

#include "RTWgui/LayerRequestProcessor.h"

// Window data
extern const std::string_view WINDOW_TITLE;
extern const unsigned WINDOW_WIDTH;
extern const unsigned WINDOW_HEIGHT;

// Main font data
extern const std::string_view MAIN_FONT_PATH;
extern const unsigned MAIN_FONT_SZ;

// Main layers data
extern const size_t MAIN_LAYER_COUNT;

void initializeLayers(LayerOwningArray &, float, float);
#endif
