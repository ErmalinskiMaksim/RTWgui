#ifdef USE_SDL
#include "RTWgui/LibraryDependent/Window.h"

Window::Window(std::string_view title, unsigned width, unsigned height)
    : m_window{SDL_CreateWindow(title.data(), width, height, 0), SDL_DestroyWindow}
{
    if (!m_window) {
        SDL_Log("Error creating a window: %s", SDL_GetError());
        throw;
    }

    // allow the typing
    SDL_StartTextInput(m_window.get());
}

void Window::destroy() const {
    SDL_StopTextInput(m_window.get());
}

WindowPtrType Window::get() const noexcept {
    return m_window.get();
}
#endif
