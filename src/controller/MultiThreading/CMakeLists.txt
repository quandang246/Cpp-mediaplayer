# Add the source files
set(SOURCES
    ActiveObject.cpp
    DispatchQueue.cpp
)

# Link the pthread library
find_package(Threads REQUIRED)

# Create the library
add_library(multithreading ${SOURCES})

target_link_libraries(multithreading Threads::Threads)
