cmake_minimum_required(VERSION 3.16.3)

project(media VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(mediaConfig.h.in mediaConfig.h)

add_subdirectory(media_lib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC media_lib)

target_include_directories(${PROJECT_NAME} PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_SOURCE_DIR}/media_lib")

install(TARGETS media DESTINATION bin)
