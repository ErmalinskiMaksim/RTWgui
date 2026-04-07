#include "RTWgui/GUI.h"
// init
#include "RTWgui/Init.h"

GUI::GUI() : m_layers(MAIN_LAYER_COUNT)
            , m_focusStack{}
            , m_libLT{}
            , m_renderer{WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT}
            , m_mainFont{MAIN_FONT_PATH, MAIN_FONT_SZ, m_renderer.get()}
{
    // initialize the layers in the ascending order
    initializeLayers(m_layers, m_mainFont.getCharacterWidth(), m_mainFont.getCharacterHeight());
    // by default the lowest layer has focus
    if (!MAIN_LAYER_COUNT) throw;
    m_focusStack.push(m_layers[0].get());
}

bool GUI::processEvents() {
    // convert lib event to internal event
    auto guiEvent = translateEvent(waitEvent(m_renderer.get()));
    if (!guiEvent) return true;
    
    return std::visit([&](auto&& ev) {
        using T = std::decay_t<decltype(ev)>;

        if constexpr (std::is_same_v<T, QuitEvent>)
            return false;
        // if event logically can propagate through layers
        else if constexpr (std::is_same_v<T, MouseLeftDownEvent>
                        || std::is_same_v<T, MouseLeftUpEvent>
                        || std::is_same_v<T, MouseRightUpEvent>
                        || std::is_same_v<T, MouseMotionEvent>) {
            // find a target layer that must consume the event and quit
            ILayer* target = nullptr;
            // search in reverse order (from the top of z-stack to the bottom)
            for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
                // event consumption is hit test based
                if ((*it)->hitTest(ev.x, ev.y)) {
                    // set focus to this layer
                    target = it->get();
                    m_focusStack.push(target);
                    // let the layer consume the event
                    target->dispatchEvents(ev);
                    break;  
                }
            }
        }// if an event should not logically propagate  
        else if constexpr (std::is_same_v<T, MouseScrollingEvent>
                        || std::is_same_v<T, TextInputEvent>
                        || std::is_same_v<T, KeyUpEvent>) {
            if (ILayer* layer = m_focusStack.top())
                layer->dispatchEvents(ev);
        }
        
        // requests can be chained
        while (processRequests());

        return true;
    }, *guiEvent);    
}

bool GUI::processRequests() {
    // fetch requests of the focused layer
    auto req = m_focusStack.top()->readRequest();
    if (!req) return false; // no pending requests
    
    auto status = LayerRequestProcessor::process(&*req, m_layers, m_focusStack);
    switch(status) {
        case LayerRequestProcessor::OperationStatus::LAYER_CREATED: { 
            // XXX REQUEST IS __ MOVED FROM __ AT THIS POINT 
            // false == a new layer that was created first must process events before 
            // making requests, thus no chain of requests
            return false;
        }
        case LayerRequestProcessor::OperationStatus::LAYER_DESTROYED: {
            // pass the final response of the destroyed layer to its caller
            std::visit([&](auto&& closeReq) {
                using T = std::decay_t<decltype(closeReq)>;
                if constexpr (std::is_same_v<T, MenuCloseRequest>
                        || std::is_same_v<T, DialogCloseRequest>
                        || std::is_same_v<T, PopupCloseRequest>) {
                    if (closeReq.resp) 
                        m_focusStack.top()->onResponse(std::move(*closeReq.resp));
                }
            }, std::move(*req));
            // true == the layer that was given focus after the destruction of the
            // previous focused layer may want to immediately leave a new request
            // after receiving previous layer's response, thus chain of requests.
            // It allows gui to react to events instantly
            return true;
        }
        default: return false; // unknown status; so far, no point to care
    }
}

void GUI::update() {
    for (auto&& layer : m_layers)
        layer->update();
}

void GUI::draw() const {
    // draw main background
    m_renderer.clear(Color4{0xFF, 0xFF, 0xFF, 0xFF}); 
    // let all the layers draw themselves in the down->top order
    for(auto&& layer : m_layers)
        layer->draw(m_renderer, m_mainFont);

    // present in a centralized maner
    m_renderer.present();
}
