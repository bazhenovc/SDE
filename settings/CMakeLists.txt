cmake_minimum_required(VERSION 2.6)

project(sde-settings)

find_package(Qt4 REQUIRED)
set(QT_USE_QTDBUS TRUE)
include(${QT_USE_FILE})

add_definitions(-Wall -pipe)
add_definitions(${QT_DEFINITIONS})

include_directories(include)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/usr/include/sde)

qt4_wrap_ui(FORM_SOURCES ui/MainWindow.ui
                                                 ui/DesktopMenu/ConfigureAppletsWidget.ui)
qt4_wrap_cpp(MOC_SOURCES include/MainWindow.hh
                                                 include/WidgetPushButton.hh
                                                 include/DesktopMenu.hh
                                                 include/DesktopMenu/ConfigureAppletsWidget.hh)

add_executable(sde-settings source/main.cc
                                                        source/MainWindow.cc
                                                        source/DesktopMenu.cc
                                                        source/DesktopMenu/ConfigureAppletsWidget.cc
                                                        ${FORM_SOURCES}
                                                        ${MOC_SOURCES})
target_link_libraries(sde-settings ${QT_LIBRARIES} sde)

INSTALL(TARGETS sde-settings
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
