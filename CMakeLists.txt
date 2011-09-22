cmake_minimum_required(VERSION 2.6)

project(sde)

include_directories(libsde/include)

add_subdirectory(libsde)
add_subdirectory(appview)
add_subdirectory(desktop)
add_subdirectory(panel)
add_subdirectory(picview)
add_subdirectory(session)
add_subdirectory(settings)
add_subdirectory(applets)
add_subdirectory(artwork)
