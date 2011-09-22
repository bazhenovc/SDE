cmake_minimum_required(VERSION 2.6)

project(sde-analogclock-applet)


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

qt4_wrap_cpp(MOC_SOURCES include/AnalogClockWidget.hh)

add_library(sde-analogclock-applet SHARED source/applet.cc
										   source/AnalogClockWidget.cc
										   ${MOC_SOURCES})
target_link_libraries(sde-analogclock-applet sde ${QT_LIBRARIES})

INSTALL(TARGETS sde-analogclock-applet
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
)

INSTALL(FILES data/clock.png data/hourhand.png data/minutehand.png
		DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/data)
