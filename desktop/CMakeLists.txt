cmake_minimum_required(VERSION 2.6)

project(sde-desktop)

find_package(Qt4 REQUIRED)
set(QT_USE_QTDBUS TRUE)
include(${QT_USE_FILE})


include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

qt4_wrap_cpp(MOC_SOURCES include/Workspace.hh
												 include/WorkspaceControl.hh)

add_executable(sde-desktop source/main.cc
																source/Workspace.cc
																source/WorkspaceControl.cc
																${MOC_SOURCES}
																${FORM_HEADERS})
target_link_libraries(sde-desktop sde ${QT_LIBRARIES})

INSTALL(TARGETS sde-desktop
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

INSTALL(FILES data/default.jpg data/menu.png
				DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/data)

set(ARTWORK data/apps.png
			data/black.png
			data/close.png
			data/keyboard.png
			data/panel.png
			data/settings.png
			data/system.png
			data/wallpaper.png
			data/winlist.png)

INSTALL(FILES ${ARTWORK}
				DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sde/data)
