add_library(Controller MediaManagement.cpp)
include_directories(../module)

target_link_libraries(Controller Module)
