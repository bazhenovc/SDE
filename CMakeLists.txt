cmake_minimum_required(VERSION 2.6)

project(sde)

include_directories(libsde/include)

set(SDE_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${SDE_ROOT_DIR})
set(LIBRARY_OUTPUT_PATH ${SDE_ROOT_DIR})

add_subdirectory(libsde)
add_subdirectory(appview)
add_subdirectory(desktop)
add_subdirectory(panel)
add_subdirectory(picview)
add_subdirectory(session)
add_subdirectory(settings)
add_subdirectory(applets)
add_subdirectory(artwork)
add_subdirectory(winman)
