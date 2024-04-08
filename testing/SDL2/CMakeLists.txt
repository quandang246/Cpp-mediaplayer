cmake_minimum_required(VERSION 3.0)
project(musicPlayer)

# Add the source file
set(SOURCES
    musicPlayer.cpp
)

# Find SDL2 libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add the executable
add_executable(musicPlayer ${SOURCES})

# Link SDL2 libraries
target_link_libraries(musicPlayer ${SDL2_LIBRARIES})
target_link_libraries(musicPlayer SDL2_image)
target_link_libraries(musicPlayer SDL2_ttf)
target_link_libraries(musicPlayer SDL2_mixer)
target_link_libraries(musicPlayer rt)
