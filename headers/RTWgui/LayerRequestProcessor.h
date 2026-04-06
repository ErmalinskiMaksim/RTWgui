#ifndef LAYER_REQUEST_PROCESSOR_H
#define LAYER_REQUEST_PROCESSOR_H

// layer logic
#include "RTWgui/ILayer.h"
#include "RTWgui/Layer.h"
#include "RTWgui/LayerFocusStack.h"

// interactors
#include "RTWgui/Interactors/MenuInteractor.h"
#include "RTWgui/Interactors/DialogInteractor.h"
#include "RTWgui/Interactors/PopupInteractor.h"

#include <memory>

using LayerOwningArray = std::vector<std::unique_ptr<ILayer>>;

// A class responsible for changing the state of layer stacks when a request comes in
class LayerRequestProcessor {
public:
    enum class OperationStatus : uint8_t { UNKNOWN, LAYER_CREATED, LAYER_DESTROYED };
    // XXX the request is getting moved inside the function in the layer creation path 
    // It's passed by pointer because the requests are not copyable. 
    static OperationStatus process(Requests* req, LayerOwningArray& layers, LayerFocusStack& fstack) noexcept {
        // if layer requests destruction of itself, return null
        if (std::holds_alternative<MenuCloseRequest>(*req)
            || std::holds_alternative<DialogCloseRequest>(*req)
            || std::holds_alternative<PopupCloseRequest>(*req)) {

            fstack.pop();
            layers.pop_back();

            return OperationStatus::LAYER_DESTROYED;
        }

        // if a layer request another layer's construction, build a layer
        if (auto* menuReq = std::get_if<MenuCreateRequest>(req)) {
            layers.push_back(
                    std::make_unique<Layer<Widget, EmptyHandlerContext, MenuCreateRequest, MenuInteractor>>(
                        std::move(*menuReq)));
        } else if (auto* dialogReq = std::get_if<DialogCreateRequest>(req)) {
            layers.push_back(
                    std::make_unique<Layer<Widget, EmptyHandlerContext, DialogCreateRequest, DialogInteractor>>(
                        std::move(*dialogReq)));
        } else if (auto* popupReq = std::get_if<PopupCreateRequest>(req)) {
            layers.push_back(
                    std::make_unique<Layer<Widget, EmptyHandlerContext, PopupCreateRequest, PopupInteractor>>(
                        std::move(*popupReq)));
        } else return OperationStatus::UNKNOWN;

        return OperationStatus::LAYER_CREATED;
    }
};

#endif
