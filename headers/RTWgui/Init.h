#ifndef INIT_H
#define INIT_H 

#include "RTWgui/Layer.h"
#include <memory>

// Window data
extern const std::string_view WINDOW_TITLE;
extern const unsigned WINDOW_WIDTH;
extern const unsigned WINDOW_HEIGHT;

// Main font data
extern const std::string_view MAIN_FONT_PATH;
extern const float MAIN_FONT_SZ;

// Main layers data
extern const size_t MAIN_LAYER_COUNT;

using LayerArray = std::vector<std::unique_ptr<ILayer>>;
void initializeLayers(LayerArray&, float, float);
#endif
