#ifndef TASK_BAR_INTERACTOR_H
#define TASK_BAR_INTERACTOR_H

#include "RTWgui/Interactors/Interactor.h"
#include "RTWgui/Handlers.h"
#include <tuple>
#include <array>

template<WidgetType MainWidget, HandlerContextType HandlerContext, typename... Handlers>
class TaskBarInteractor : public Interactor {
    using WidgetView = std::reference_wrapper<MainWidget>;

    template <std::size_t I>
    using Handler = std::tuple_element_t<I, std::tuple<Handlers...>>;
    using TaskNames = std::array<std::string_view, sizeof...(Handlers)>; 
    using Buttons = std::array<Rect, sizeof...(Handlers)>;
public:
    TaskBarInteractor(NonModalLayerCreateRequest::Payload&&, WidgetView widget, RequestView req) noexcept 
    : m_tasks{Handlers::getID()...}
    , m_buttons{}
    , r_widget{widget}
    , r_pendingRequest{req}
    {
        auto hbox = r_widget.get().getHitBox();
        auto w = r_widget.get().getCharWidth();
        for (auto i = 0uz; i < m_buttons.size(); ++i) {
            m_buttons[i] = {hbox.x, hbox.y, w * static_cast<float>(m_tasks[i].size()), hbox.h };
            hbox.x += m_buttons[i].w;
        }
    }

    void dispatchEvents(const LayerEvent& event) 
        noexcept(noexcept(std::visit([&](auto&& ev) { processEvents(ev); }, 
            std::declval<const LayerEvent&>())))
    {
        std::visit([&](auto&& ev) { processEvents(ev); }, event);
    }

    void update() const noexcept {}

    void render(const Renderer& renderer, const Font& font) const 
        noexcept(noexcept(std::declval<const Renderer&>().renderText(
            std::declval<const Font&>(),
            std::declval<const Rect&>(),
            std::declval<const std::string_view&>())))
    {
        // render button text
        for (auto i = 0uz; i < m_tasks.size(); ++i) 
            renderer.renderText(font, m_buttons[i], m_tasks[i]);
    }
private:
    using Interactor::processEvents;
    void processEvents(const MouseLeftDownEvent& event) 
        noexcept(noexcept(processImpl(event, std::make_index_sequence<sizeof...(Handlers)>{})))
    {
        processImpl(event, std::make_index_sequence<sizeof...(Handlers)>{});
    }
    
    template<size_t... Is>
    void processImpl(const MouseLeftDownEvent& event, std::index_sequence<Is...>) 
        // TODO 
        // noexcept((noexcept(Widget::contains(std::declval<float>(), std::declval<float>(), std::declval<Rect>()))
        //         && noexcept(Handler<Is>::requestMainMenu(std::declval<HandlerContext>()))) && ...)
    {
        ((Widget::contains(event.x, event.y, m_buttons[Is]) &&
          Handler<Is>::requestMainMenu(
              HandlerContext{r_widget.get(), r_pendingRequest})
         ), ...);
    }

    // text names of menu buttons
    TaskNames m_tasks;
    // menu buttons' hit boxes
    Buttons m_buttons;

    WidgetView r_widget;
    RequestView r_pendingRequest;
};

#endif
