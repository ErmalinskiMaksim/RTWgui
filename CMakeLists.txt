add_library(RTWgui)
include(cmake/dependencies.cmake)

target_compile_features(RTWgui PUBLIC cxx_std_23)
target_compile_options(RTWgui  PRIVATE
    -Wstrict-aliasing
    -Wall 
    -Wextra 
    -Werror
    -Wpedantic 
    -Wwrite-strings
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wfloat-equal
    -Wcast-align
    -Wimplicit-fallthrough
    -Wempty-body
    -Wuninitialized
    -Wmisleading-indentation
    -Wshadow
    -Wconversion 
    -Wsign-compare
    -Wswitch-default 
    -Wundef
)

if (GUI_ENABLE_LTO)
    set_property(TARGET RTWgui PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()

target_compile_options(RTWgui PRIVATE
    $<$<CONFIG:Debug>:
        -O0
        -g3
        -ggdb3
        -fno-elide-constructors
        -fno-strict-aliasing
        # -fno-omit-frame-pointer
        -ftrapv
        -fstack-protector-strong
    >
)

target_compile_definitions(RTWgui PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(RTWgui PRIVATE
    $<$<CONFIG:Release>:
        -O3
    >
)

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
target_sources(RTWgui PRIVATE ${src})

target_include_directories(RTWgui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)
