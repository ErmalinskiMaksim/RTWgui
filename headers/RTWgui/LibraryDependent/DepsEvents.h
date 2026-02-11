#ifndef DEPS_EVENTS_H
#define DEPS_EVENTS_H

#ifdef USE_SDL

#include "SDL3/SDL_events.h"

using LibEvent = SDL_Event;
inline LibEvent waitEvent() {
    LibEvent ev;
    SDL_WaitEvent(&ev);
    return ev;
}
 
inline auto GetMouseState(float* x, float* y) {
    return SDL_GetMouseState(x, y);
}

// EVENT TYPES
#define EVENT_TYPE(ev)          (ev.type)
#define EVENT_QUIT              SDL_EVENT_QUIT

// MOUSE BUTTON
#define EVENT_MOUSE_BUTTON_DOWN SDL_EVENT_MOUSE_BUTTON_DOWN
#define EVENT_MOUSE_BUTTON_UP   SDL_EVENT_MOUSE_BUTTON_UP
#define MOUSE_BUTTON_LEFT       SDL_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT      SDL_BUTTON_RIGHT
#define MOUSE_BUTTON_TYPE(ev)   (ev.button.button)
#define MOUSE_BUTTON_X(ev)      (ev.button.x)
#define MOUSE_BUTTON_Y(ev)      (ev.button.y)

// MOUSE MOTION
#define EVENT_MOUSE_MOTION      SDL_EVENT_MOUSE_MOTION
#define MOUSE_MOTION_X(ev)      (ev.motion.x)
#define MOUSE_MOTION_Y(ev)      (ev.motion.y)

// MOUSE WHEEL
#define EVENT_MOUSE_WHEEL       SDL_EVENT_MOUSE_WHEEL
#define MOUSE_WHEEL_X(ev)       (ev.wheel.x)
#define MOUSE_WHEEL_Y(ev)       (ev.wheel.y)

// KEYBOARD
#define EVENT_KEY_UP            SDL_EVENT_KEY_UP
#define KEY_ENTER               SDLK_RETURN
#define KEY_BACKSPACE           SDLK_BACKSPACE
#define KEY_ESCAPE              SDLK_ESCAPE                
#define KEY_TAB                 SDLK_TAB                    
#define KEY_SPACE               SDLK_SPACE                  
#define KEY_EXCLAIM             SDLK_EXCLAIM                
#define KEY_DBLAPOSTROPHE       SDLK_DBLAPOSTROPHE          
#define KEY_HASH                SDLK_HASH                   
#define KEY_DOLLAR              SDLK_DOLLAR                 
#define KEY_PERCENT             SDLK_PERCENT                
#define KEY_AMPERSAND           SDLK_AMPERSAND              
#define KEY_APOSTROPHE          SDLK_APOSTROPHE             
#define KEY_LEFTPAREN           SDLK_LEFTPAREN              
#define KEY_RIGHTPAREN          SDLK_RIGHTPAREN             
#define KEY_ASTERISK            SDLK_ASTERISK               
#define KEY_PLUS                SDLK_PLUS                   
#define KEY_COMMA               SDLK_COMMA                  
#define KEY_MINUS               SDLK_MINUS                  
#define KEY_PERIOD              SDLK_PERIOD                 
#define KEY_SLASH               SDLK_SLASH                  
#define KEY_0                   SDLK_0                      
#define KEY_1                   SDLK_1                      
#define KEY_2                   SDLK_2                      
#define KEY_3                   SDLK_3                      
#define KEY_4                   SDLK_4                      
#define KEY_5                   SDLK_5                      
#define KEY_6                   SDLK_6                      
#define KEY_7                   SDLK_7                      
#define KEY_8                   SDLK_8                      
#define KEY_9                   SDLK_9                      
#define KEY_COLON               SDLK_COLON                  
#define KEY_SEMICOLON           SDLK_SEMICOLON              
#define KEY_LESS                SDLK_LESS                   
#define KEY_EQUALS              SDLK_EQUALS                 
#define KEY_GREATER             SDLK_GREATER                
#define KEY_QUESTION            SDLK_QUESTION               
#define KEY_AT                  SDLK_AT                     
#define KEY_LEFTBRACKET         SDLK_LEFTBRACKET            
#define KEY_BACKSLASH           SDLK_BACKSLASH              
#define KEY_RIGHTBRACKET        SDLK_RIGHTBRACKET           
#define KEY_CARET               SDLK_CARET                  
#define KEY_UNDERSCORE          SDLK_UNDERSCORE             
#define KEY_GRAVE               SDLK_GRAVE                  
#define KEY_A                   SDLK_A
#define KEY_B                   SDLK_B
#define KEY_C                   SDLK_C
#define KEY_D                   SDLK_D
#define KEY_E                   SDLK_E
#define KEY_F                   SDLK_F
#define KEY_G                   SDLK_G
#define KEY_H                   SDLK_H
#define KEY_I                   SDLK_I
#define KEY_J                   SDLK_J
#define KEY_K                   SDLK_K
#define KEY_L                   SDLK_L
#define KEY_M                   SDLK_M
#define KEY_N                   SDLK_N
#define KEY_O                   SDLK_O
#define KEY_P                   SDLK_P
#define KEY_Q                   SDLK_Q
#define KEY_R                   SDLK_R
#define KEY_S                   SDLK_S
#define KEY_T                   SDLK_T
#define KEY_U                   SDLK_U
#define KEY_V                   SDLK_V
#define KEY_W                   SDLK_W
#define KEY_X                   SDLK_X
#define KEY_Y                   SDLK_Y
#define KEY_Z                   SDLK_Z
#define KEY_LEFTBRACE           SDLK_LEFTBRACE              
#define KEY_PIPE                SDLK_PIPE                   
#define KEY_RIGHTBRACE          SDLK_RIGHTBRACE             
#define KEY_TILDE               SDLK_TILDE                  
#define KEY_DELETE              SDLK_DELETE                  
#define KEY_PLUSMINUS           SDLK_PLUSMINUS               
#define KEY_CAPSLOCK            SDLK_CAPSLOCK               
#define KEY_F1                  SDLK_F1                     
#define KEY_F2                  SDLK_F2                     
#define KEY_F3                  SDLK_F3                     
#define KEY_F4                  SDLK_F4                     
#define KEY_F5                  SDLK_F5                     
#define KEY_F6                  SDLK_F6                     
#define KEY_F7                  SDLK_F7                     
#define KEY_F8                  SDLK_F8                     
#define KEY_F9                  SDLK_F9                     
#define KEY_F10                 SDLK_F10                     
#define KEY_F11                 SDLK_F11                     
#define KEY_F12                 SDLK_F12                     
#define KEYMOD_LSHIFT           SDL_KMOD_LSHIFT 
#define KEYMOD_RSHIFT           SDL_KMOD_RSHIFT 
#define KEYMOD_LCTRL            SDL_KMOD_LCTRL  
#define KEYMOD_RCTRL            SDL_KMOD_RCTRL  
#define KEYMOD_LALT             SDL_KMOD_LALT   
#define KEYMOD_RALT             SDL_KMOD_RALT   
#define KEYMOD_LSUPER           SDL_KMOD_LGUI   
#define KEYMOD_RSUPER           SDL_KMOD_RGUI
#define KEYMOD_NUM              SDL_KMOD_NUM     
#define KEYMOD_CAPS             SDL_KMOD_CAPS   
#define KEYMOD_CTRL             SDL_KMOD_CTRL
#define KEY_KEY(ev)             (ev.key.key)
#define IS_KEYMOD_CTRL(ev)      (ev.key.mod & KEYMOD_CTRL)
using KeyType = Uint32;
using ModType = Uint16;

inline bool isCTRL() {
    return SDL_GetModState() & KEYMOD_CTRL;
}

// TEXT INPUT
#define EVENT_TEXT_INPUT        SDL_EVENT_TEXT_INPUT
#define TEXT_INPUT_TEXT(ev)     (ev.text.text)
using TextType = const char*;

#elif USE_SFML

#include "SFML/Window/Event.hpp"

using LibEvent = sf::Event;
inline auto GetMouseState(float* x, float* y) {
    auto pos = sf::Mouse::getPosition();
    *x = static_cast<float>(pos.x);
    *y = static_cast<float>(pos.y);
}

inline bool isCTRL() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || 
    sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
}

// EVENT TYPES
#define EVENT_TYPE(ev)          (ev.type)
#define EVENT_QUIT              sf::Event::Closed

// MOUSE BUTTON
#define EVENT_MOUSE_BUTTON_DOWN sf::Event::MouseButtonPressed
#define EVENT_MOUSE_BUTTON_UP   sf::Event::MouseButtonReleased
#define MOUSE_BUTTON_LEFT       sf::Mouse::Left
#define MOUSE_BUTTON_RIGHT      sf::Mouse::Right
#define MOUSE_BUTTON_TYPE(ev)   (ev.mouseButton.button)
#define MOUSE_BUTTON_X(ev)      (static_cast<float>(ev.mouseButton.x))
#define MOUSE_BUTTON_Y(ev)      (static_cast<float>(ev.mouseButton.y))

// MOUSE MOTION
#define EVENT_MOUSE_MOTION      sf::Event::MouseMoved
#define MOUSE_MOTION_X(ev)      (static_cast<float>(ev.mouseMove.x))
#define MOUSE_MOTION_Y(ev)      (static_cast<float>(ev.mouseMove.y))

// MOUSE WHEEL
#define EVENT_MOUSE_WHEEL       sf::Event::MouseWheelScrolled
#define MOUSE_WHEEL_X(ev)       (ev.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel ? static_cast<float>(ev.mouseWheelScroll.delta) : 0.0f)
#define MOUSE_WHEEL_Y(ev)       (ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel ? static_cast<float>(ev.mouseWheelScroll.delta) : 0.0f)

// KEYBOARD
#define EVENT_KEY_UP            sf::Event::KeyReleased
#define KEY_Q                   sf::Keyboard::Q
#define KEY_ENTER               sf::Keyboard::Enter
#define KEY_BACKSPACE           sf::Keyboard::BackSpace
#define KEY_KEY(ev)             (ev.key.code)
#define IS_KEYMOD_CTRL(ev)      (ev.key.control)
using KeyType = sf::Keyboard::Key;

// TEXT INPUT
#define EVENT_TEXT_INPUT        sf::Event::TextEntered
#define TEXT_INPUT_TEXT(ev)     (sf::String(event.text.unicode).toAnsiString())
using TextType = std::string;
#endif 

#endif
