#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef USE_SDL
#include "RTWgui/LibraryDependent/DepsRendering.h"
#include <string_view>

class Texture {
public:
    Texture();
    Texture(RendererPtrType, float, float);
    Texture(RendererPtrType, SurfacePtrType);
    Texture(RendererPtrType, std::string_view);

    TexturePtrType get() const noexcept;
    bool empty() const noexcept;

    void setBlendMode() noexcept;
    void resetBlendMode() noexcept;
private:
    TextureType m_texture;
};
#endif
#endif
