cmake_minimum_required (VERSION 3.8)

project("Bounce-CPP")

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})