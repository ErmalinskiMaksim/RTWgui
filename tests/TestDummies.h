#include "RTWgui/Layer.h"

struct CallTracer {
    void record (std::string name) {
        log.push_back(std::move(name));
    }
    std::vector<std::string> log;
};

class TestRenderer : public Renderer {};
class TestFont : public Font {};

struct TestHandlerContext {
    std::reference_wrapper<const Widget> widget;
    RequestView req;
};

class TestWidget : public Widget {
    template<WidgetType, HandlerContextType, typename...>
    friend class TestInteractor;
public:
    TestWidget(Widget&&) {}
    void setTracer(CallTracer* ct) { p_tracer = ct; }
    void render(const Renderer&, const Font&) const noexcept {
        if (p_tracer) p_tracer->record("TestWidget::render");
    }
private:
    CallTracer* p_tracer;
};

template<WidgetType MainWidget, HandlerContextType HandlerContext, typename... Handlers>
class TestInteractor : public Interactor {
    using WidgetView = std::reference_wrapper<MainWidget>;
public:
    TestInteractor(NonModalLayerCreateRequest::Payload&& payload, WidgetView widget, RequestView req) noexcept 
    : r_widget{widget}
    , r_pendingRequest{req}
    {
        p_tracer = static_cast<CallTracer*>(payload.ctx);
        r_widget.get().setTracer(p_tracer);
    }

    void dispatchEvents(const LayerEvent& event) {
        // std::visit([&](auto&& ev) { processEvents(ev); }, event);
        r_widget.get().p_tracer->record("TestInteractor::dispatchEvents");
    }

    void update() const noexcept {
        r_widget.get().p_tracer->record("TestInteractor::update");
    }
    
    void render(const Renderer&, const Font&) const noexcept {
        r_widget.get().p_tracer->record("TestInteractor::render");
    }
private:
    WidgetView r_widget;
    RequestView r_pendingRequest;
    CallTracer* p_tracer;
};


