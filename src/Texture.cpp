#include "RTWgui/LibraryDependent/Texture.h"

#ifdef USE_SDL

Texture::Texture() 
    : m_texture{nullptr, SDL_DestroyTexture}
{}

Texture::Texture(RendererPtrType renderer, float width, float height)
    : m_texture{
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            static_cast<int>(width),
            static_cast<int>(height))
    , SDL_DestroyTexture}
{
    if (!m_texture) {
        SDL_Log("Error creating a texture: %s", SDL_GetError());
        throw;
    }
}

Texture::Texture(RendererPtrType renderer, SurfacePtrType surf) 
    : m_texture{
        SDL_CreateTextureFromSurface(renderer, surf)
        , SDL_DestroyTexture
    }
{
    if (!m_texture) {
        SDL_Log("Error creating a texture from surface: %s", SDL_GetError());
        throw;
    }
}

TexturePtrType Texture::get() const noexcept {
    return m_texture.get();
}

bool Texture::empty() const noexcept {
    return !m_texture;
}

#endif
