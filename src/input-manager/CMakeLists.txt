add_library(InputManager InputManager.cpp)
target_link_libraries(InputManager
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)