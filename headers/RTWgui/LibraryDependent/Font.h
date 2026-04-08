#ifndef FONT_H
#define FONT_H

#include "RTWgui/LibraryDependent/Texture.h"
#include <string_view>

#ifdef USE_SDL
class Font {
public:
    #ifdef USE_TEST
    Font(); 
    #endif
    Font(std::string_view, unsigned, RendererPtrType);
    Font(Font&&) = delete;
    Font& operator=(Font&&) = delete;

    TexturePtrType getGlyphAtlas() const noexcept;  
    float getCharacterWidth() const noexcept;
    float getCharacterHeight() const noexcept;
private:
    void prerenderGlyphAtlas(RendererPtrType);

    FontType m_font;
    Texture m_glyphAtlas;
};
#elif USE_SFML

class Font {
public:
    #ifdef 
    Font() = default;
    #endif
    Font(std::string_view, unsigned, RendererViewType );

    float getCharacterWidth() const;
    float getCharacterHeight() const;
    unsigned size() const;
    FontViewType get() const; 

private:
    FontType m_font;
    unsigned m_fontSize;
};
#endif
#endif
