cmake_minimum_required(VERSION 3.16.3)

project(media VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(mediaConfig.h.in mediaConfig.h)

include_directories(src)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Controller Module)

target_include_directories(${PROJECT_NAME} PUBLIC 
                        "${PROJECT_BINARY_DIR}")

install(TARGETS media DESTINATION bin)
