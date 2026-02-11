#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef USE_SDL
#include "RTWgui/LibraryDependent/DepsRendering.h"

class Texture {
public:
    Texture();
    Texture(RendererPtrType, float, float);
    Texture(RendererPtrType, SurfacePtrType);
    TexturePtrType get() const noexcept;
    bool empty() const noexcept;
private:
    TextureType m_texture;
};
#endif
#endif
