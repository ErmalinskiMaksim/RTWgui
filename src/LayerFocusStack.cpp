#include "RTWgui/LayerFocusStack.h"

void LayerFocusStack::push(ILayer* layer) noexcept {
    // if not itself -> set focus 
    if (!m_layers.empty() && m_layers.back() == layer) return;
    m_layers.push_back(layer);
}

void LayerFocusStack::pop() noexcept {
    if (!m_layers.empty())
        m_layers.pop_back();
}

ILayer* LayerFocusStack::top() const noexcept {
    return m_layers.empty() ? nullptr : m_layers.back();
}

