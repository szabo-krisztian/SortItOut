add_library(App App.cpp)

add_subdirectory(../input-manager input-manager-build)
add_subdirectory(../sync-vector sync-vector-build)

target_include_directories(App
    PUBLIC
    ../input-manager
    ../sync-vector
)

target_link_libraries(App
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    InputManager
    SyncVector
)