cmake_minimum_required(VERSION 3.16.3)

project(media VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

configure_file(mediaConfig.h.in mediaConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

install(TARGETS media DESTINATION bin)
