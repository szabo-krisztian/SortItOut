cmake_minimum_required(VERSION 3.10)
project(Sort_It_Out_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 CONFIG REQUIRED)


#add_subdirectory(input-manager)
add_subdirectory(app)

add_executable(Main main.cpp)

target_include_directories(Main
    PRIVATE
    app
)

target_link_libraries(Main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    App
)