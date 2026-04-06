#ifndef LAYER_FOCUS_STACK_H
#define LAYER_FOCUS_STACK_H

#include <vector>

class ILayer;

// a non-ownig focus layer stack 
// * holds a state of focus stack 
// * each operation is safe (has checks)
class LayerFocusStack {
public:
    void push(ILayer*) noexcept;
    void pop() noexcept;
    ILayer* top() const noexcept;
private:
    std::vector<ILayer*> m_layers;
};

#endif
