#ifndef RENDERER_H
#define RENDERER_H

#include "RTWgui/LibraryDependent/Font.h"

#ifdef USE_SDL
class Renderer {
public:
    #ifdef USE_TEST
    Renderer(); 
    #endif
    Renderer(std::string_view, unsigned, unsigned);
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    ~Renderer();

    RendererPtrType get() const noexcept;

    void renderLines(const Point*, int, Color4) const noexcept;
    void renderFillRect(const Rect* const, Color4) const noexcept;
    void renderRect(const Rect* const, Color4) const noexcept;    
    void renderText(const Font&, Rect, std::string_view) const noexcept;
    void renderTexture(TexturePtrType, const Rect*, const Rect*) const noexcept;

    void clear(Color4) const noexcept;
    void present() const noexcept;

    void setTarget(TexturePtrType) const noexcept;
    void setTarget() const noexcept; 

    void setBlendMode() const noexcept;
    void resetBlendMode() const noexcept;
    
private: 
    WindowType m_window;
    mutable RendererType m_renderer;
};

#elif USE_SFML
struct Rect {
    operator FRect() const noexcept;
    float x;
    float y;
    float w;
    float h;
};


class Renderer {
public:
    #ifdef 
    Renderer() = default; 
    #endif // 
    Renderer(std::string_view, unsigned, unsigned);
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    RendererViewType get() const noexcept;

    void renderLines(const Point*, int, Color4) const;
    void renderFillRect(const Rect* const, Color4) const;
    void renderRect(const Rect* const, Color4) const;    
    void renderText(const Font&, Rect, std::string_view) const;

    void clear() const;
    void present() const;
    
private: 
    mutable RendererType m_renderer;
};


#endif

#endif
