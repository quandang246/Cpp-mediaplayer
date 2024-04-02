# Add the source files
set(SOURCES
    MediaManagement.cpp
    musicPlayer.cpp
)

# Include directories
include_directories(../module)
# Find SDL2 libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Create the library
add_library(Controller ${SOURCES})

# Link the required libraries, assuming Module is another library
target_link_libraries(Controller Module)
# Link SDL2 libraries
target_link_libraries(Controller ${SDL2_LIBRARIES})
target_link_libraries(Controller SDL2_image)
target_link_libraries(Controller SDL2_ttf)
target_link_libraries(Controller SDL2_mixer)
target_link_libraries(Controller rt)
