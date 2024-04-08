cmake_minimum_required(VERSION 3.16.3)

project(multithreading_actor_pattern)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

# Link the pthread library
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
