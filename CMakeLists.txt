cmake_minimum_required(VERSION 3.16.3)

project(media VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(mediaConfig.h.in mediaConfig.h)

include_directories(src
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/toolkit
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/ape
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/mpeg
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/mpeg/id3v1
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/mpeg/id3v2
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/taglib/mpeg/id3v2/frames
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/taglib/bindings/c/
                    )

if(NOT BUILD_SHARED_LIBS)
    add_definitions(-DTAGLIB_STATIC)
endif()
                    
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
                        Module
                        Controller
                        tag  
                    )

target_include_directories(${PROJECT_NAME} PUBLIC 
                        "${PROJECT_BINARY_DIR}")

install(TARGETS media 
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        DESTINATION bin
        )
