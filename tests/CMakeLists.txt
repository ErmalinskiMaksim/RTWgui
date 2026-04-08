file(GLOB TEST_SOURCES ./*.cpp)
add_executable(RTWguiTests ${TEST_SOURCES})

target_compile_definitions(RTWgui
    PUBLIC USE_TEST
)

# CppUTest
find_package(CppUTest QUIET)
if(NOT CppUTest_FOUND)
    add_subdirectory(external/cpputest)
endif()

target_link_libraries(RTWguiTests PRIVATE
    RTWgui
    CppUTest
    CppUTestExt
)

add_test(NAME RTWguiTests COMMAND RTWguiTests)
