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
            width,
            height)
    , SDL_DestroyTexture}
{
    if (!m_texture) {
        SDL_Log("Error creating a texture: %s", SDL_GetError());
        throw;
    }
}

Texture::Texture(RendererPtrType renderer, SurfacePtrType surf) 
    : m_texture{
        SDL_CreateTextureFromSurface(renderer, surf.get())
        , SDL_DestroyTexture
    }
{
    if (!m_texture) {
        SDL_Log("Error creating a texture from surface: %s", SDL_GetError());
        throw;
    }
}

TexturePtrType Texture::get() const {
    return m_texture.get();
}

#endif
