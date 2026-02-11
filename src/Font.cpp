#include "RTWgui/LibraryDependent/Font.h"

#ifdef USE_SDL
Font::Font(RendererPtrType renderer, std::string_view path, float fontSz)
    : m_font{TTF_OpenFont(path.data(), fontSz), TTF_CloseFont}
    , m_glyphAtlas{}
{
    if (!m_font) {
        SDL_Log("Error opening a font: %s", SDL_GetError());
        throw;
    }
    prerenderGlyphAtlas(renderer);
}

void Font::destroy() {
    m_font.reset();
}

void Font::prerenderGlyphAtlas(RendererPtrType renderer) {
    // create a string of ASCII symbols 32 through 95
    char atlas[96];
    for(int i = 0; i < 95; ++i) atlas[i] = static_cast<char>(i + 32);
    atlas[95] = '\0';

    // create a texture surface to draw the glyph atlas on
    SurfaceType textSurf = {
        TTF_RenderText_Blended(m_font.get(), atlas, 0, {0x00, 0x00, 0x00, 0xff}),
        SDL_DestroySurface
    };
    if(!textSurf) return false;

    Texture glyphAtlas{renderer, textSurf.get()};
    std::swap(m_glyphAtlas, glyphAtlas);
}

TexturePtrType Font::getGlyphAtlas() const noexcept {
    return m_glyphAtlas.get();
}

float Font::getCharacterWidth() const noexcept {
    return (m_glyphAtlas) ? static_cast<float>(m_glyphAtlas->w) / 95 : 0.0f;
}

float Font::getCharacterHeight() const noexcept {
    return (m_glyphAtlas) ? static_cast<float>(m_glyphAtlas->h) : 0.0f; 
}

#elif USE_SFML
#include <iostream>
Font::Font(std::string_view path, unsigned fontSz)
    : m_fontSize(fontSz) 
{
    if (!m_font.loadFromFile(std::string(path))) {
        std::cerr << "Error opening font: " << path << std::endl;
        throw std::runtime_error("Failed to load font");
    }
}

float Font::getCharacterWidth() const {
    return m_font.getGlyph(' ', m_fontSize, false).advance;
}

float Font::getCharacterHeight() const {
    return m_font.getLineSpacing(m_fontSize);
}

unsigned Font::size() const {
    return m_fontSize;
}

FontViewType Font::get() const {
    return m_font; 
}

#endif
