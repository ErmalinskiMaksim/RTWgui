include(FetchContent)

if (GRAPHICS_LIBRARY STREQUAL "SDL")
    message(STATUS "Using SDL backend")

    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

    # --- SDL3 ---
    FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/sdl.git
        GIT_TAG        main
    )

    # --- SDL3_TTF ---
    FetchContent_Declare(
        sdl3_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/sdl_ttf.git
        GIT_TAG        main
    )

    FetchContent_MakeAvailable(sdl3 sdl3_ttf)

    target_link_libraries(RTWgui
        PUBLIC
            SDL3::SDL3
            SDL3_ttf::SDL3_ttf
    )

    target_compile_definitions(RTWgui
        PUBLIC USE_SDL
    )

elseif (GRAPHICS_LIBRARY STREQUAL "SFML")

    message(STATUS "Using SFML backend")

    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(SFML_INSTALL OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/sfml/sfml.git
        GIT_TAG        2.6.1
    )

    FetchContent_MakeAvailable(sfml)

    target_link_libraries(RTWgui
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-system
    )

    target_compile_definitions(RTWgui
        PUBLIC USE_SFML
    )

else()
    message(FATAL_ERROR
        "Invalid GRAPHICS_LIBRARY: ${GRAPHICS_LIBRARY} (expected SDL or SFML)"
    )
endif()
