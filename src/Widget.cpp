#include "RTWgui/Widgets/Widget.h"


Color Color::operator+(Color1 delta) const {
    return Color(r + delta, delta + g, delta + b, a);
}

Color Color::operator-(Color1 delta) const {
    return Color(r - delta, g - delta, b - delta, a);
}

Color::operator Color4() const noexcept {
    return Color4(r, g, b, a);
}

Widget::Widget(Rect&& hitBox, Color fillColor, Color outlineColor
            , float charWidth, float charHeight) 
    : m_texture{}
    , m_hitBox(hitBox)
    , m_fillColor(fillColor)
    , m_outlineColor(outlineColor)
    , m_charWidth(charWidth)
    , m_charHeight(charHeight)
{}

void Widget::render(const Renderer& renderer, const Font&) const noexcept {
    if (m_texture.empty()) [[unlikely]] {
        Rect textureRect = { 0.0f, 0.0f, m_hitBox.w, m_hitBox.h };
        Texture upToDateTexture{renderer.get(), textureRect.w, textureRect.h};

        renderer.setTarget(upToDateTexture.get());
        renderer.clear();
        renderer.renderFillRect(&textureRect, m_fillColor);
        renderer.renderRect(&textureRect, m_outlineColor);
        renderer.setTarget();

        std::swap(m_texture, upToDateTexture);
    }

    renderer.renderTexture(m_texture.get(), &m_hitBox);
}

Rect Widget::getHitBox() const noexcept {
    return m_hitBox;
}

Color Widget::getFillColor() const noexcept {
    return m_fillColor;
}

Color Widget::getOutlineColor() const noexcept {
    return m_outlineColor;
}

float Widget::getCharWidth() const noexcept {
    return m_charWidth;
}

float Widget::getCharHeight() const noexcept {
    return m_charHeight;
}

