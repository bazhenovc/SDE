cmake_minimum_required(VERSION 2.6)

project(libsde)


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt4_wrap_cpp(MOC_SOURCES include/IconWidget.hh
						 include/PanelWidget.hh
						 include/AppletWidget.hh)

add_library(sde SHARED source/NetWM.cc
						source/Applet.cc
						source/IconWidget.cc
						source/PanelWidget.cc
						source/PanelWidget_setGeometry.cc
						source/FileUtils.cc
						source/AppletWidget.cc
						source/SdeApplication.cc
						${MOC_SOURCES})
target_link_libraries(sde X11 ${QT_LIBRARIES})

INSTALL(TARGETS sde
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

INSTALL(FILES include/Applet.hh
			  include/AppletWidget.hh
			  include/FileUtils.hh
			  include/IconWidget.hh
			  include/NetWM.hh
			  include/PanelWidget.hh
			  include/SdeApplication.hh
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/sde)

