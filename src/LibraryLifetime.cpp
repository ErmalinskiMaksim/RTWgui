#include "RTWgui/LibraryDependent/LibraryLifetime.h"

#ifdef USE_SDL 
#include "RTWgui/LibraryDependent/DepsRendering.h"
#endif

LibraryLifetime::LibraryLifetime() {
    if (!s_isInitialized) {
        #ifdef USE_SDL 
        constexpr SDL_InitFlags SDL_FLAGS = SDL_INIT_VIDEO;         
        if (!SDL_Init(SDL_FLAGS) || !TTF_Init()) throw;
        #endif
        s_isInitialized = true;
    }
}

LibraryLifetime::~LibraryLifetime() {
    #ifdef USE_SDL
        TTF_Quit();
        SDL_Quit();
    #endif
    s_isInitialized = false;
}
