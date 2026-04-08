#ifndef LAYER_H
#define LAYER_H

#include "RTWgui/ILayer.h"
#include "RTWgui/Handlers.h"
#include "RTWgui/Interactors/Interactor.h"

template<typename T>
concept InteractorWithOperation = 
        std::is_base_of_v<Interactor, T>
        && requires (T t) {
            { t.getOperation() };
            { t.processOperation() } -> std::same_as<void>;
        };

template<WidgetType MainWidget
        , HandlerContextType HandlerContext
        , CreateRequestType CreateRequest
        , template<WidgetType, HandlerContextType, typename...> class Interactor
        , typename... Handlers>
requires (ResponseHandlerFor<HandlerContext, Handlers> && ...)
class Layer final : public ILayer {
    using InteractorType = Interactor<MainWidget, HandlerContext, Handlers...>;
public:
    Layer (CreateRequest&& req, Handlers&&... handlers)
    : m_widget(std::move(req.widget))
    , m_interactor{std::move(req.payload), std::ref(m_widget), std::ref(m_pendingRequest)}
    , m_handlers{handlers...}
    , m_dispatcher{} 
    {}

    /// Layer's interface ///
    void dispatchEvents(const LayerEvent& event) override {
        m_interactor.dispatchEvents(event);
    }

    void update() override {
        m_interactor.update();
    }

    // Behavior:
    // 1. allows widget to render first
    // 2. allows interactor to render after widget
    void draw(const Renderer& renderer, const Font& font) const override {
        m_widget.render(renderer, font);
        m_interactor.render(renderer, font);
    }

    // dispatch responses to a correct action handler
    void onResponse(Responses&& resp) override {
        if constexpr (std::is_same_v<CreateRequest, NonModalLayerCreateRequest>) {
            std::apply([&](auto&... handlers) {
                m_dispatcher.dispatch(
                    std::move(resp)
                    , [&]() noexcept {
                        if constexpr (InteractorWithOperation<InteractorType>) 
                            return HandlerContext{ std::ref(m_widget), std::ref(m_pendingRequest)
                                                , m_interactor.getOperation()};
                        else return HandlerContext{ std::ref(m_widget), std::ref(m_pendingRequest)};
                        }()
                    , handlers...
                    );
                }, m_handlers);
            if constexpr (InteractorWithOperation<InteractorType>) m_interactor.processOperation();
        }
    }

    constexpr bool hitTest(float x, float y) const noexcept override {
        if constexpr (std::is_same_v<CreateRequest, NonModalLayerCreateRequest>) {
            return m_widget.contains(x, y);
        } else return true;
    }
protected:
    // main widget of the layer
    MainWidget m_widget;
    // main interactor of the layer with the widget
    InteractorType m_interactor;

    // action handlers of the layer and a dispatcher for handlers
    // If a layer is modal, then they should not exist
    [[no_unique_address]] std::tuple<Handlers...> m_handlers;
    [[no_unique_address]] ResponseDispatcher<HandlerContext, Handlers...> m_dispatcher;
};

#endif
