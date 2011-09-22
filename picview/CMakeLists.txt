cmake_minimum_required(VERSION 2.6)

project(sde-picview)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})


include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

qt4_wrap_cpp(MOC_SOURCES include/PicView.hh)

add_executable(sde-picview source/main.cc
						   source/PicView.cc
						   ${MOC_SOURCES}
						   ${FORM_HEADERS})
target_link_libraries(sde-picview sde ${QT_LIBRARIES})

INSTALL(TARGETS sde-picview
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
