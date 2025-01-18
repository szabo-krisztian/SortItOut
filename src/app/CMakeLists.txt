add_library(App App.cpp)

add_subdirectory(../input-manager ../build)

target_include_directories(App
    PUBLIC
    ../input-manager
)

target_link_libraries(App
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    InputManager
)