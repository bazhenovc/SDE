cmake_minimum_required(VERSION 2.6)

project(sde-clock-applet)


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

qt4_wrap_cpp(MOC_SOURCES include/BatteryWidget.hh)

add_library(sde-battery-applet SHARED source/applet.cc
										   source/BatteryWidget.cc
										   ${MOC_SOURCES})
target_link_libraries(sde-battery-applet sde ${QT_LIBRARIES})

INSTALL(TARGETS sde-battery-applet
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
)
