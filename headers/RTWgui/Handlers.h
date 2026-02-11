#ifndef HANDLERS_H
#define HANDLERS_H

#include "RTWgui/Requests.h"
// global operation register. Those are the kinds of operations that 
// are performed by the caller upon handler completion. Hanlders were 
// initially supposed to handle static operations on global singletons 
// but then some specific kind of operations emerged which demanded a
// signal passing mechanism between callers and handlers.
// TODO maybe improve later
template<typename Ctx, typename H, typename R>
concept CanHandleResponse =
    requires(Ctx ctx, H& h, R&& r) {
        { h.dispatch(static_cast<R&&>(r), ctx)} -> std::same_as<bool>;
        { H::getID() };
        { H::requestMainMenu(ctx) } -> std::same_as<bool>;
    };

template<typename Ctx, typename H, typename Variant>
struct HandlesAny;

template<typename Ctx, typename H, typename... Rs>
struct HandlesAny<Ctx, H, std::variant<Rs...>>
    : std::bool_constant<(CanHandleResponse<Ctx, H, Rs> || ...)> {};

template<typename Ctx, typename H>
concept ResponseHandler =
    HandlesAny<Ctx, H, Responses>::value;

template<typename Ctx, typename H>
concept ResponseHandlerFor =
    ResponseHandler<Ctx, H>;
// This class is responsible for dispatching responses to a correct
// action handler
template<typename Ctx, typename... Handlers>
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

struct EmptyHandlerContext{};
using EmptyResponseDispatcher = ResponseDispatcher<EmptyHandlerContext>;
#endif 
