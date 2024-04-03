cmake_minimum_required(VERSION 3.0)
project(main)

# Add the source file
set(SOURCES
    main.cpp
)

# Find SDL2 libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf)
target_link_libraries(${PROJECT_NAME} SDL2_mixer)
target_link_libraries(${PROJECT_NAME} rt)
