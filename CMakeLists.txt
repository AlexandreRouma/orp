cmake_minimum_required(VERSION 3.13)
project(demo)

file(GLOB_RECURSE SRC "demo/*.cpp", "orp/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE "orp/")