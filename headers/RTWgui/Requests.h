#ifndef REQUESTS_H
#define REQUESTS_H

#include <functional>
#include <string_view>
#include <type_traits>
#include <vector>
#include <optional>
#include "RTWgui/Responses.h"
#include "RTWgui/Widgets/Widget.h"

// Requests are a mechanism that enables layers to communicate
// with GUI upstream. They are used to let any layer ask for a 
// new layer creation or deletion 
//
// They follow the same pattern: 
// * create requests contain everything necessary to construct
//   a new layer
// * close requests contain a response from the layer that 
//   requests to be destroyed
//
// Structure:
// * create requests all have an internal Payload struct to unify the
//   interface of creating them. It may contain different context-specific
//   objects. Widget is obligatory for them though
// * close requests all have a response inside. It's a unified way of
//   communicating the last message that a layer wants to send (e.g. a menu 
//   communicates the action that user chose; a dialog communicates the 
//   text input that user has entered). 

struct NonModalLayerCreateRequest {
    Widget widget;
    struct Payload{
        void* ctx = nullptr; // type-erased context
    } payload;
};

struct MenuCreateRequest {
    struct Payload {
        struct MenuAction { // entry: (action name; action ID)
            std::string_view text;
            ActionID id;
        };
        std::vector<MenuAction> entries; // menu entries
    };
    Widget widget;
    Payload payload;
};

struct MenuCloseRequest {
    std::optional<MenuResponse> resp; 
};

struct DialogCreateRequest {
    struct Payload {
        std::optional<std::string_view> title;
        // text that a dialog has in the input field before 
        // user provides any input
        std::optional<std::string_view> initInput; 
        uint8_t maxInputLen;
    };
    Widget widget;
    Payload payload;
};

struct DialogCloseRequest {
    std::optional<DialogResponse> resp;
};

struct PopupCreateRequest {
    struct Payload {
        // text of a pop-up formatted as lines
        std::vector<std::string_view> lines;
    };
    Widget widget;
    Payload payload; 
};

struct PopupCloseRequest {
    std::optional<PopupResponse> resp;
};

using Requests = std::variant<MenuCreateRequest
            , MenuCloseRequest
            , DialogCreateRequest
            , DialogCloseRequest
            , PopupCreateRequest
            , PopupCloseRequest
    >;  
using OptRequest = std::optional<Requests>;
using RequestView = std::reference_wrapper<OptRequest>;

template<typename T>
concept RequestType = std::is_same_v<T, NonModalLayerCreateRequest>
                    || std::is_same_v<T, MenuCreateRequest> 
                    || std::is_same_v<T, MenuCloseRequest>
                    || std::is_same_v<T, DialogCreateRequest>
                    || std::is_same_v<T, DialogCloseRequest>
                    || std::is_same_v<T, PopupCreateRequest>
                    || std::is_same_v<T, PopupCloseRequest>
                    ;

// a concept that is used in layer construction 
template<typename T>
concept CreateRequestType = std::is_same_v<T, NonModalLayerCreateRequest>
                        || std::is_same_v<T, MenuCreateRequest>
                        || std::is_same_v<T, DialogCreateRequest>
                        || std::is_same_v<T, PopupCreateRequest>;

#endif
