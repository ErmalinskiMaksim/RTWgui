#ifndef HANDLERS_H
#define HANDLERS_H

#include "RTWgui/Requests.h"

// Minimum requirements for a custom handler
template<typename Ctx, typename H, typename R>
concept CanHandleResponse =
    requires(Ctx ctx, H& h, R&& r) {
        // a default way of receiving responses.
        // NOTE: bool return type is used to signal if a response 
        // was consumed or not: true == consumed, false == not consumed.
        // This mechanism allows to propagate the response until a 
        // correct handler catches it and disallows it to proceed further.
        { h.dispatch(static_cast<R&&>(r), ctx)} -> std::same_as<bool>;
        // XXX ID function may be useful to store the name of the object
        // that is tied to it (e.g. button name), though it's far from 
        // being a perfect solution and may be depricated in the future
        { H::getID() };
        // a function that defines and implements request creation. For 
        // example, if you want to create a menu, then define widget parameters,
        // text layout, actions, etc. in this function. Pay attention to the word
        // menu actions - I prefer defining them as an enum inside of a handler.
        // They should have a type that is compatible with ActionID (see Responses.h)
        { H::requestMainMenu(ctx) } -> std::same_as<bool>;
    };

template<typename Ctx, typename H, typename Variant>
struct HandlesAny;

template<typename Ctx, typename H, typename... Rs>
struct HandlesAny<Ctx, H, std::variant<Rs...>>
    : std::bool_constant<(CanHandleResponse<Ctx, H, Rs> || ...)> {};

template<typename Ctx, typename H>
concept ResponseHandler = HandlesAny<Ctx, H, Responses>::value;

// this concept should exist because handlers can (and probably should)
// be template classes
template<typename Ctx, typename H>
concept ResponseHandlerFor = ResponseHandler<Ctx, H>;

// This class is responsible for dispatching responses to a correct
// action handler. To find an appropriate handler, it propagates the 
// response until some handler signals that it caught it. 
template<typename Ctx, typename... Handlers>
// XXX to allow template response handlers
requires (... && ResponseHandler<Ctx, Handlers>)
struct ResponseDispatcher {
    static bool dispatch(Responses&& r, Ctx ctx, Handlers&... hs) {
        return std::visit([&](auto&& resp) -> bool {
            using R = std::remove_cvref_t<decltype(resp)>;

            return (( [&]<typename H>(H& h) {
                if constexpr (CanHandleResponse<Ctx, H, R>)
                    return h.dispatch(static_cast<decltype(resp)&&>(resp),ctx);
                else return false;
                }(hs) ) || ...);
        }, std::forward<Responses>(r));
    }
};

// a stub for layers that do not need handler mechanism
struct EmptyHandlerContext{};
using EmptyResponseDispatcher = ResponseDispatcher<EmptyHandlerContext>;
#endif 
