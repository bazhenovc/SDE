cmake_minimum_required(VERSION 2.6)

project(sde-panel)


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

qt4_wrap_cpp(MOC_SOURCES include/Panel.hh
						 include/LookAndFeelWidget.hh
						 include/PanelMenu.hh)

qt4_wrap_ui(FORM_SOURCES ui/LookAndFeelWidget.ui)

add_library(sde-panel-applet SHARED source/main.cc
							  source/Panel.cc
							  source/LookAndFeelWidget.cc
							  source/PanelMenu.cc
							  ${MOC_SOURCES}
							  ${FORM_SOURCES})
target_link_libraries(sde-panel-applet sde ${QT_LIBRARIES})

INSTALL(TARGETS sde-panel-applet
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/applets
)
